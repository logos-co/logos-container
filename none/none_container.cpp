// The "none" container: this build starts no process, so modules run only
// in-process and no channel process (such as a spawned runtime) exists.
#include <logos_container/channel_process.h>
#include <logos_container/container_factory.h>

namespace LogosCore {

std::shared_ptr<ModuleContainer> makeContainer() {
    return nullptr;
}

std::unique_ptr<ChannelProcess> startChannelProcess(const std::string& /*executable*/,
                                                    const std::vector<std::string>& /*args*/,
                                                    ChannelCallbacks /*callbacks*/) {
    return nullptr;
}

} // namespace LogosCore
