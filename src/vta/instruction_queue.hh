#ifndef INSTRUCTION_QUEUE_HH
#define INSTRUCTION_QUEUE_HH

#include "base/circular_queue.hh"
#include "params/InstructionQueue.hh"
#include "sim/clocked_object.hh"
#include "vta/base/vta_instruction.hh"

namespace gem5
{
class InstructionQueue : public ClockedObject
{
  private:
    CircularQueue<VTAInstruction *> queue;
    Tick latency;

  public:
    PARAMS(InstructionQueue);

    InstructionQueue(const Params &params);

    VTAInstruction *&front();

    void pushBack(VTAInstruction *instruction);

    void popFront();
};
} // namespace gem5

#endif
