#ifndef DATA_QUEUE_HH
#define DATA_QUEUE_HH

#include "params/DataQueue.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{
class DataQueue : public SimObject
{
  private:
    vta::DependencyQueue dependencyQueue;

  public:
    PARAMS(DataQueue);

    DataQueue(const Params &params);

    auto
    push(bool f = true) -> void
    {
        dependencyQueue.push(f);
    }

    auto
    pop() -> void
    {
        dependencyQueue.pop();
    }

    auto
    tryPush(bool f = true) -> bool
    {
        if (dependencyQueue.full()) {
            return false;
        }
        dependencyQueue.push(f);
        return true;
    }

    auto
    tryPop() -> bool
    {
        if (dependencyQueue.empty()) {
            return false;
        }
        dependencyQueue.pop();
        return true;
    }
};
} // namespace gem5

#endif
