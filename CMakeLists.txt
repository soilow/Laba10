cmake_minimum_required(VERSION 3.12)
project(labwork10)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC scheduler)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)