
cmake_minimum_required(VERSION 3.1)

project(Json)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_BUILD_TYPE Debug)


add_executable(main 
        src/main.cpp 
)


add_library(json
  src/json.cpp
  src/json.h
  src/log.h
)


target_link_libraries(main json)

add_subdirectory(third_party/googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(null_test
test/null_test.cpp
        
)

target_link_libraries(null_test json gtest gtest_main)

enable_testing()
add_test(NAME json_test COMMAND null_test)

