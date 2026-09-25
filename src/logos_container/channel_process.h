#ifndef LOGOS_CONTAINER_CHANNEL_PROCESS_H
#define LOGOS_CONTAINER_CHANNEL_PROCESS_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace LogosCore {

// A child process that is not a module, such as the runtime host an app spawns.
// The parent talks to it in lines over a private channel, the child's stdin and
// stdout, which nothing logs; its stderr is the child's log.
struct ChannelCallbacks {
    std::function<void(const std::string& line)> onLine;    // from its stdout
    std::function<void(const std::string& line)> onLog;     // from its stderr
    std::function<void(int exitCode, bool crashed)> onExit; // never after terminate()
};

class ChannelProcess {
public:
    virtual ~ChannelProcess() = default;

    // One line on its stdin, which stays open. False once that is closed.
    virtual bool writeLine(const std::string& line) = 0;
    // EOF on its stdin.
    virtual void closeInput() = 0;
    // Asks it to exit, then forces it, and returns once it is gone.
    virtual void terminate() = 0;
    virtual int64_t pid() const = 0;
};

// Link-time seam, like makeContainer(): the container implementation the build
// links defines it. The callbacks run on that implementation's threads. A child
// that must not outlive its parent watches the parent itself.
// nullptr if the process could not be started.
std::unique_ptr<ChannelProcess> startChannelProcess(const std::string& executable,
                                                    const std::vector<std::string>& args,
                                                    ChannelCallbacks callbacks);

} // namespace LogosCore

#endif // LOGOS_CONTAINER_CHANNEL_PROCESS_H
