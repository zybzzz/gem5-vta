#ifndef INSTRUCTION_QUEUE_HH
#define INSTRUCTION_QUEUE_HH

#include "base/types.hh"
#include "params/InstructionQueue.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{
class InstructionQueue : public SimObject
{
  private:
    vta::CommandQueue commandQueue;
    Cycles pushLatency;
    Cycles popLatency;

  public:
    PARAMS(InstructionQueue);

    InstructionQueue(const Params &params);

    // Time information is returned to the caller for statistical purposes
    auto
    pop() -> vta::TickStruct<vta::Instruction>
    {
        return commandQueue.pop();
    }

    auto
    push(const vta::Instruction &value) -> vta::TickStruct<>
    {
        return commandQueue.push(value);
    }

    auto
    empty() const noexcept -> bool
    {
        return commandQueue.empty();
    }

    auto
    full() const noexcept -> bool
    {
        return commandQueue.full();
    }

    auto
    size() const noexcept -> size_t
    {
        return commandQueue.size();
    }
};
} // namespace gem5

#endif
