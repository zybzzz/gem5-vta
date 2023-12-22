#ifndef INSTRUCTION_QUEUE_HH
#define INSTRUCTION_QUEUE_HH

#include "params/InstructionQueue.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{
class InstructionQueue : public SimObject
{
  private:
  public:
    PARAMS(InstructionQueue);

    InstructionQueue(const Params &params);

    int pushBack();

    auto popFront() -> vta::Instruction *;

    auto
    empty() const noexcept -> bool
    {
        // TODO
        return false;
    };
};
} // namespace gem5

#endif
