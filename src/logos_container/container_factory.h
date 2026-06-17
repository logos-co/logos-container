#ifndef LOGOS_CONTAINER_FACTORY_H
#define LOGOS_CONTAINER_FACTORY_H

#include "module_container.h"
#include <memory>

namespace LogosCore {

// Link-time seam for selecting the default container implementation.
//
// The definition is provided by whichever container implementation library the
// build links in (e.g. logos-container-subprocess), upcasting its concrete type
// to this interface. This contract names no implementation, and consumers
// (logos-liblogos) call this instead of constructing a concrete container — so
// the implementation is chosen purely at build/link time.
//
// Exactly one provider should be linked. Returns the container instance.
std::shared_ptr<ModuleContainer> makeContainer();

} // namespace LogosCore

#endif // LOGOS_CONTAINER_FACTORY_H
