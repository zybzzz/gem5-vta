#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue(const Params &params) :
    ClockedObject(params),
    queue(params.queue_size),
    readLatency(params.read_latency),
    writeLatency(params.write_latency)
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

} // namespace gem5
