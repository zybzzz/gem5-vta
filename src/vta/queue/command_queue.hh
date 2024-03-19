#ifndef COMMAND_QUEUE_HH
#define COMMAND_QUEUE_HH

#include "params/CommandQueue.hh"
#include "sim/sim_object.hh"
#include "vta/queue/queue.hh"
#include "vta/vta.hh"
#include "vta/vta_hw_config.hh"

namespace gem5
{

class CommandQueue : public Queue<vta::Instruction, vta::STREAM_IN_DEPTH, 1, 1>
{
  public:
    PARAMS(CommandQueue);

    CommandQueue(const Params &params) : Queue{params} {}
};

} // namespace gem5

#endif
