#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue(const Params &params) :
    SimObject(params),
    pushLatency(params.push_latency),
    popLatency(params.pop_latency)
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

} // namespace gem5
