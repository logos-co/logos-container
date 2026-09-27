# The generic container-implementation config (as logos-container-subprocess
# ships), for "none": LogosContainerImpl::impl is this archive and needs nothing else.
get_filename_component(_logos_container_impl_prefix "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

if(NOT TARGET LogosContainerImpl::impl)
  add_library(LogosContainerImpl::impl STATIC IMPORTED)
  set_target_properties(LogosContainerImpl::impl PROPERTIES
    IMPORTED_LOCATION "${_logos_container_impl_prefix}/lib/liblogos_container_none.a"
  )
endif()

unset(_logos_container_impl_prefix)
