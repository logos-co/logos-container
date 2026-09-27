# The "none" container implementation, for a runtime embedded in an app that may
# not spawn (iOS): both link-time seams return nullptr.
add_library(logos_container_none STATIC none_container.cpp)
target_link_libraries(logos_container_none PUBLIC logos_container)

# Its own package, without the contract headers: the archive and the generic
# LogosContainerImpl config that a consumer (liblogos) find_package's.
install(TARGETS logos_container_none ARCHIVE DESTINATION lib COMPONENT none)
install(FILES LogosContainerImplConfig.cmake
    DESTINATION lib/cmake/LogosContainerImpl COMPONENT none)
