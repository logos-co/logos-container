# logos-container

The **container contract** for Logos modules on liblogos and every
container implementation (e.g. `logos-container-subprocess`).

It declares the `ModuleContainer` interface (`module_container.h`) and two
link-time seams:
- `container_factory.h`, `LogosCore::makeContainer()`: the build's default
  container.
- `channel_process.h`, `LogosCore::startChannelProcess()`: a child that is not a
  module (the runtime host an app spawns), which the parent talks to in lines
  over its stdin and stdout.

A consumer (liblogos) calls them without naming a concrete type; the
*definitions* are provided by whichever implementation library is linked in.

This repo also ships one such implementation, `none` (`none/`): both seams return
nullptr, so no process is ever started, for a runtime embedded in an app that may
not spawn (iOS). Like logos-container-subprocess it installs the `LogosContainerImpl`
CMake config, so a consumer selects it by putting `.#none` on `CMAKE_PREFIX_PATH`.

## Build & test

```bash
nix build .#logos-container                  # the installed headers
nix build .#none                             # the none implementation
nix build .#checks.aarch64-linux.tests -L    # run the contract and none tests
```

Consume it from CMake via the `logos_container` INTERFACE target (carries the
include path + `nlohmann_json`), or include headers directly as
`<logos_container/module_container.h>`.
