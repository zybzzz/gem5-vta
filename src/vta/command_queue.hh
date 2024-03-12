#ifndef COMMAND_QUEUE_HH
#define COMMAND_QUEUE_HH

#include "params/CommandQueue.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{

class CommandQueue : public SimObject, public vta::CommandQueue
{
  public:
    PARAMS(CommandQueue);
    CommandQueue(const Params &params) : SimObject{params} {}
};

} // namespace gem5

#endif
