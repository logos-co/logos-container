# The container contract: the Qt-free ModuleContainer interface, the
# ModuleDescriptor / LoadedModuleHandle value types it exchanges, and the
# shared module-name allowlist that guards the container's token-socket path.
# Header-only — there is nothing to compile, so this is an INTERFACE library.
#
# The module loader / format-loader strategy interfaces are NOT here: those are
# a core concern and live in logos-liblogos.
add_library(logos_container INTERFACE)

# nlohmann_json is part of the public interface (ModuleDescriptor carries
# nlohmann::json members), so consumers that pull in these headers get the
# imported target.
target_link_libraries(logos_container INTERFACE
    nlohmann_json::nlohmann_json
)

# Two interfaces so both include spellings resolve:
#   <logos_container/module_container.h>  (cross-repo, mirrors process-stats)
#   "module_container.h"                   (bare, as the contract headers
#                                            include each other)
target_include_directories(logos_container INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/logos_container>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/logos_container>
)
