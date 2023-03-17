set(GTest_ROOT /usr/src/googletest/googletest)
add_subdirectory(${GTest_ROOT}
        "${CMAKE_CURRENT_BINARY_DIR}/googletest" EXCLUDE_FROM_ALL)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(main_test main.cpp test_a_star.cpp)

add_test(NAME main_test COMMAND main_test)

target_link_libraries(main_test PUBLIC gtest_main)