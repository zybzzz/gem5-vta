#ifndef DEPENDENCY_QUEUE_HH
#define DEPENDENCY_QUEUE_HH

#include "params/DependencyQueue.hh"
#include "sim/sim_object.hh"
#include "vta/queue/queue.hh"
#include "vta/vta_hw_config.hh"

namespace gem5
{

class DependencyQueue : public Queue<bool, vta::STREAM_IN_DEPTH, 1, 1>
{
  public:
    PARAMS(DependencyQueue);

    DependencyQueue(const Params &params) : Queue{params} {}
};

} // namespace gem5

#endif
