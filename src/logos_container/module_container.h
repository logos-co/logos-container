#ifndef MODULE_CONTAINER_H
#define MODULE_CONTAINER_H

#include "load_status.h"
#include "module_descriptor.h"
#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace LogosCore {

// Abstract interface for module isolation / execution environments.
// A container decides *where* and *how* a module process runs (subprocess,
// docker, in-process, etc.) but knows nothing about the module type.
class ModuleContainer {
public:
    virtual ~ModuleContainer() = default;

    virtual std::string id() const = 0;

    virtual bool canHandle(const ModuleDescriptor& desc) const = 0;

    // Launch a module inside this container.  The caller (CompositeModuleLoader)
    // supplies the resolved host binary and CLI arguments — those come from
    // the ModuleLoader, not the container.
    virtual bool launch(const ModuleDescriptor& desc,
                        const std::string& hostBinary,
                        const std::vector<std::string>& args,
                        std::function<void(const std::string& name)> onTerminated,
                        LoadedModuleHandle& out) = 0;

    virtual bool sendToken(const std::string& name, const std::string& token) = 0;

    // Wait, bounded, for the one thing launch() cannot know: whether the
    // module's plugin actually loaded. Returns as soon as the child reports a
    // verdict or dies, so the common cases cost what the child costs and only a
    // silent, live child waits out `timeout`.
    //
    // The default is Unknown — the honest answer for a container that cannot
    // observe what became of its children — and leaves the caller's behaviour
    // exactly as it was before this existed.
    virtual LoadOutcome awaitLoad(const std::string& /*name*/,
                                  std::chrono::milliseconds /*timeout*/) {
        return {};
    }

    virtual void terminate(const std::string& name) = 0;

    virtual void terminateAll() = 0;

    virtual bool hasModule(const std::string& name) const = 0;

    virtual std::optional<int64_t> pid(const std::string& /*name*/) const { return std::nullopt; }

    virtual std::unordered_map<std::string, int64_t> getAllPids() const { return {}; }
};

} // namespace LogosCore

#endif // MODULE_CONTAINER_H
