// The "none" implementation, linked as a consumer links it: neither seam ever
// starts a process.
#include <gtest/gtest.h>

#include <logos_container/channel_process.h>
#include <logos_container/container_factory.h>

#include <string>

TEST(NoneContainer, MakesNoContainer) {
    EXPECT_EQ(LogosCore::makeContainer(), nullptr);
}

TEST(NoneContainer, StartsNoChannelProcess) {
    bool called = false;
    LogosCore::ChannelCallbacks callbacks;
    callbacks.onLine = [&](const std::string&) { called = true; };
    callbacks.onLog = [&](const std::string&) { called = true; };
    callbacks.onExit = [&](int, bool) { called = true; };
    EXPECT_EQ(LogosCore::startChannelProcess("/bin/sh", {"-c", "echo started"}, callbacks),
              nullptr);
    EXPECT_FALSE(called);
}
