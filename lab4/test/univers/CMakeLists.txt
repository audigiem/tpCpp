enable_testing()

# Add test files
add_executable(test_univers_getters test_univers_getters.cpp)
add_executable(test_univers_setters test_univers_setters.cpp)
add_executable(test_univers_add_particle test_univers_add_particle.cpp)
add_executable(test_univers_update test_univers_update.cpp)

# Link with GTest
target_link_libraries(test_univers_getters gtest gtest_main pthread)
target_link_libraries(test_univers_setters gtest gtest_main pthread)
target_link_libraries(test_univers_add_particle gtest gtest_main pthread)
target_link_libraries(test_univers_update gtest gtest_main pthread)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(test_univers_getters)
gtest_discover_tests(test_univers_setters)
gtest_discover_tests(test_univers_add_particle)
gtest_discover_tests(test_univers_update)

# Add a test for performance (without registering it with CTest)
add_executable(test_univers_perf test_univers_perf.cpp)