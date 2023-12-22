#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue(const Params &params) : SimObject(params)
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

int
InstructionQueue::pushBack()
{
    return 0;
}

auto
InstructionQueue::popFront() -> vta::Instruction *
{
    return nullptr;
}

} // namespace gem5
