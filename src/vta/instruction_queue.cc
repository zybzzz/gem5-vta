#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue(const Params &params) :
    ClockedObject(params), queue(params.queue_size), latency(params.latency)
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

VTAInstruction *&
InstructionQueue::front()
{
    return queue.front();
}

void
InstructionQueue::pushBack(VTAInstruction *instruction)
{
    // TODO Perform delay-related operations
    queue.push_back(instruction);
}

void
InstructionQueue::popFront()
{
    queue.pop_front();
}

} // namespace gem5
