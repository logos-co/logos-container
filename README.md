# logos-container

The **container contract** for Logos modules on liblogos and every
container implementation (e.g. `logos-container-subprocess`).

## Build & test

```bash
nix build .#logos-container                  # the installed headers
nix build .#checks.aarch64-linux.tests -L    # run the contract tests
```

Consume it from CMake via the `logos_container` INTERFACE target (carries the
include path + `nlohmann_json`), or include headers directly as
`<logos_container/module_container.h>`.
