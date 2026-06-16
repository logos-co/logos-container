// Self-contained tests for the logos-container contract: the shared module
// name allowlist, the ModuleDescriptor/LoadedModuleHandle value types, and the
// ModuleContainer interface. These are the pieces every container
// implementation and liblogos itself depend on, so a regression here breaks the
// whole stack.
#include <gtest/gtest.h>

#include <logos_container/module_name_validation.h>
#include <logos_container/module_descriptor.h>
#include <logos_container/module_container.h>

#include <functional>
#include <optional>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// isValidModuleName — the allowlist guarding the token-socket path segment
// ---------------------------------------------------------------------------

TEST(ModuleNameValidation, AcceptsSimpleNames) {
    EXPECT_TRUE(logos::isValidModuleName("chat"));
    EXPECT_TRUE(logos::isValidModuleName("my_module"));
    EXPECT_TRUE(logos::isValidModuleName("waku-module"));
    EXPECT_TRUE(logos::isValidModuleName("ABC123"));
}

TEST(ModuleNameValidation, RejectsEmptyAndOverlong) {
    EXPECT_FALSE(logos::isValidModuleName(""));
    EXPECT_FALSE(logos::isValidModuleName(std::string(65, 'a')));
    EXPECT_TRUE(logos::isValidModuleName(std::string(64, 'a')));
}

TEST(ModuleNameValidation, RejectsPathSeparatorsAndTraversal) {
    EXPECT_FALSE(logos::isValidModuleName("x/y"));
    EXPECT_FALSE(logos::isValidModuleName("x\\y"));
    EXPECT_FALSE(logos::isValidModuleName(".."));
    EXPECT_FALSE(logos::isValidModuleName("."));
    EXPECT_FALSE(logos::isValidModuleName("a/../b"));
    EXPECT_FALSE(logos::isValidModuleName("with space"));
    EXPECT_FALSE(logos::isValidModuleName(std::string("nul\0byte", 8)));
}

// ---------------------------------------------------------------------------
// Value types compile and carry their fields
// ---------------------------------------------------------------------------

TEST(ModuleDescriptor, DefaultsAndAssignment) {
    LogosCore::ModuleDescriptor desc;
    desc.name = "m";
    desc.format = "qt-plugin";
    desc.rawMetadata = nlohmann::json::object();
    EXPECT_EQ(desc.name, "m");
    EXPECT_EQ(desc.format, "qt-plugin");

    LogosCore::LoadedModuleHandle handle;
    EXPECT_EQ(handle.pid, -1);
    handle.name = "m";
    EXPECT_EQ(handle.name, "m");
}

// A minimal ModuleContainer implementation must compile against the interface.
namespace {
class NullContainer : public LogosCore::ModuleContainer {
public:
    std::string id() const override { return "null"; }
    bool canHandle(const LogosCore::ModuleDescriptor&) const override { return false; }
    bool launch(const LogosCore::ModuleDescriptor&, const std::string&,
                const std::vector<std::string>&,
                std::function<void(const std::string&)>,
                LogosCore::LoadedModuleHandle&) override { return false; }
    bool sendToken(const std::string&, const std::string&) override { return false; }
    void terminate(const std::string&) override {}
    void terminateAll() override {}
    bool hasModule(const std::string&) const override { return false; }
};
} // namespace

TEST(ModuleContainer, InterfaceIsImplementable) {
    NullContainer c;
    EXPECT_EQ(c.id(), "null");
    EXPECT_FALSE(c.hasModule("x"));
    EXPECT_FALSE(c.pid("x").has_value());        // default impl
    EXPECT_TRUE(c.getAllPids().empty());          // default impl
}
