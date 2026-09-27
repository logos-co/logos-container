# Logos Container contract tests

add_executable(logos_container_tests
    test_contract.cpp
)

target_link_libraries(logos_container_tests PRIVATE
    logos_container
    GTest::gtest
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)

target_include_directories(logos_container_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

gtest_discover_tests(logos_container_tests)

# The "none" implementation on its own, as a consumer links it.
add_executable(logos_container_none_tests
    test_none.cpp
)

target_link_libraries(logos_container_none_tests PRIVATE
    logos_container_none
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(logos_container_none_tests)
