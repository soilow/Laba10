add_library(graph Graph.h Graph.cpp)
add_library(node Node.h Node.cpp)

target_link_libraries(graph PUBLIC node)