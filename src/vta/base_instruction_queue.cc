#include "vta/base_instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
BaseInstructionQueue::BaseInstructionQueue(const Params &params) :
    SimObject(params)
{
    DPRINTF(BaseVTAFlag, "create BaseInstructionQueue!\n");
}

int
BaseInstructionQueue::pushBack()
{
    return 0;
}

int
BaseInstructionQueue::popFront()
{
    return 0;
}

} // namespace gem5
