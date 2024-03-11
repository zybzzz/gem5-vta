#ifndef DEPENDENCY_QUEUE_HH
#define DEPENDENCY_QUEUE_HH

#include "params/DependencyQueue.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{

class DependencyQueue : public SimObject, public vta::DependencyQueue
{
  public:
    PARAMS(DependencyQueue);
    DependencyQueue(const Params &params) : SimObject(params) {}
};

} // namespace gem5

#endif
