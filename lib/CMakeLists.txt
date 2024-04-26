add_library(scheduler Scheduler.cpp Scheduler.h)

add_subdirectory(Graph)

target_link_libraries(scheduler PUBLIC graph)