#include "vta/instruction_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionQueue::InstructionQueue()
{
    DPRINTF(BaseVTAFlag, "create InstructionQueue!\n");
}

InstructionQueue::InstructionQueue(Tick readLatency, Tick writeLatency) :
    readLatency(readLatency), writeLatency(writeLatency)
{}
} // namespace gem5
