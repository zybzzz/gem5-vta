#ifndef INSTRUCTION_FETCH_MODULE_HH
#define INSTRUCTION_FETCH_MODULE_HH

#include <string>
#include <string_view>

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/port.hh"
#include "params/InstructionFetchModule.hh"
#include "sim/sim_object.hh"
#include "vta/instruction_queue.hh"
#include "vta/vta.hh"
#include "vta/vta_const.hh"

namespace gem5
{

class InstructionFetchModule : public SimObject
{
  private:
    class InstructionPort : public RequestPort
    {
      private:
        InstructionFetchModule &owner;

      public:
        InstructionPort(
            const std::string_view name, InstructionFetchModule &owner) :
            RequestPort{std::string{name}}, owner{owner}
        {}

      protected:
        auto
        recvTimingResp(PacketPtr pkt) -> bool override
        {
            return true;
        }

        auto
        recvReqRetry() -> void override
        {}

        auto
        sendRetryResp() -> void override
        {}
    } instruction_port;

    InstructionQueue *loadCommandQueue;
    InstructionQueue *computeCommandQueue;
    InstructionQueue *storeCommandQueue;

    class ProgressEvent : public Event
    {
      private:
        InstructionFetchModule &owner;

      public:
        ProgressEvent(InstructionFetchModule &owner) : owner{owner} {}

        auto
        process() -> void override
        {
            owner.reschedule(this, curTick() + 1);
        }
    } event{*this};

  public:
    PARAMS(InstructionFetchModule);

    InstructionFetchModule(const Params &params) :
        SimObject{params},
        instruction_port{params.name + ".instruction_port", *this},
        loadCommandQueue{params.load_command_queue},
        computeCommandQueue{params.compute_command_queue},
        storeCommandQueue{params.store_command_queue}
    {
        DPRINTF(BaseVTAFlag, "create InstructionFetchModule!\n");

        vta::Instruction *instruction_vec{};
        size_t instruction_count{};
        // handle the situation with queue full
        for (size_t pc{}; pc != instruction_count; ++pc) {
            const auto instruction{instruction_vec[pc]};
            const auto opcode{instruction.opcode()};
            switch (opcode) {
            case vta::Opcode::LOAD:
                if (const auto memory_type{
                        instruction.asMemoryInstruction().memory_type};
                    memory_type == vta::MemoryId::INPUT ||
                    memory_type == vta::MemoryId::WEIGHT) {
                    DPRINTF(BaseVTAFlag, "instruction to load\n");
                    // loadCommandQueue << instruction;
                    loadCommandQueue->push(instruction);
                } else {
                    DPRINTF(BaseVTAFlag, "instruction to compute\n");
                    // computeCommandQueue << instruction;
                    computeCommandQueue->push(instruction);
                }
                break;
            case vta::Opcode::STORE:
                DPRINTF(BaseVTAFlag, "instruction to store\n");
                // storeCommandQueue << instruction;
                storeCommandQueue->push(instruction);
                break;
            case vta::Opcode::FINISH:
                break;
            default:
                DPRINTF(BaseVTAFlag, "instruction to compute\n");
                // computeCommandQueue << instruction;
                computeCommandQueue->push(instruction);
                break;
            }
        }
    }

    auto
    startup() -> void override
    {
        schedule(event, curTick());
    }

    auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == std::string_view{"instruction_port"}) {
            return instruction_port;
        }
        return SimObject::getPort(if_name, idx);
    }
};

} // namespace gem5

#endif
