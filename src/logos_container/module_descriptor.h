#ifndef MODULE_DESCRIPTOR_H
#define MODULE_DESCRIPTOR_H

#include <any>
#include <cstdint>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// Qt-free value types passed across the container boundary. A ModuleContainer
// receives a ModuleDescriptor describing what to launch and fills in a
// LoadedModuleHandle on success. These are the only types the container
// contract needs to know about — the ModuleLoader / ModuleFormatLoader
// strategy interfaces that also consume them live in the core (liblogos).

namespace LogosCore {

// Describes a module the core wants to load/launch.
struct ModuleDescriptor {
    std::string name;
    std::string path;                      // path to the module binary/bundle/wasm/etc.
    std::string format;                    // "qt-plugin", "wasm", "" (empty = default)
    std::vector<std::string> dependencies;
    std::string instancePersistencePath;   // empty if not configured
    std::vector<std::string> modulesDirs;  // directories siblings are looked up in
    nlohmann::json rawMetadata;            // metadata parsed from manifest.json
    nlohmann::json loaderConfig;           // optional: {"id":"docker","image":"..."}, etc.

    // Per-module transport set, serialized as JSON (see
    // logos-cpp-sdk/cpp/logos_transport_config_json.h for the wire
    // shape). Empty = inherit the global default (LocalSocket only).
    // Threaded through to the child subprocess by ModuleLoader
    // implementations so its LogosAPIProvider binds every transport
    // in the set rather than only the global default.
    std::string transportSetJson;
};

// A handle to a successfully loaded module. Stored in ModuleRegistry (ModuleInfo).
struct LoadedModuleHandle {
    std::string name;
    int64_t pid = -1;      // -1 when not process-based (in-proc, wasm, remote, etc.)
    std::string endpoint;  // transport-specific URI, e.g. "qtro+unix://my_module"
    std::any opaque;       // loader-private state (optional)
};

} // namespace LogosCore

#endif // MODULE_DESCRIPTOR_H
