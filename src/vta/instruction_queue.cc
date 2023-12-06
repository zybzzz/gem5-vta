#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

InstructionQueue::InstructionQueue(
    BaseVTA *vta, Tick readLatency, Tick writeLatency) :
    vta(vta), readLatency(readLatency), writeLatency(writeLatency)
{}
} // namespace gem5
