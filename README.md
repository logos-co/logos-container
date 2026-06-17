# logos-container

The **container contract** for Logos modules on liblogos and every
container implementation (e.g. `logos-container-subprocess`).

It declares two things: the `ModuleContainer` interface
(`module_container.h`) and a link-time factory seam
(`container_factory.h`, `LogosCore::makeContainer()`). A consumer (liblogos)
calls `makeContainer()` to obtain the build's default container without naming a
concrete type; the *definition* is provided by whichever implementation library
is linked in.

## Build & test

```bash
nix build .#logos-container                  # the installed headers
nix build .#checks.aarch64-linux.tests -L    # run the contract tests
```

Consume it from CMake via the `logos_container` INTERFACE target (carries the
include path + `nlohmann_json`), or include headers directly as
`<logos_container/module_container.h>`.
