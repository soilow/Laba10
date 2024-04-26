#include "Scheduler.h"

void TTaskScheduler::ExecuteAll() const {
    std::stack<unsigned> sorted = graph.TopSort();
    size_t stack_size = sorted.size();
    
    for (size_t i = 0; i < stack_size; ++i) {
        graph.nodes[sorted.top()]->Calculate();
        sorted.pop();
    }
}