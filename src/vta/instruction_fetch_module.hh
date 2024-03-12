#ifndef INSTRUCTION_FETCH_MODULE_HH
#define INSTRUCTION_FETCH_MODULE_HH

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

#include "base/trace.hh"
#include "base/types.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/packet.hh"
#include "mem/packet_access.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/InstructionFetchModule.hh"
#include "sim/cur_tick.hh"
#include "sim/sim_object.hh"
#include "vta/command_queue.hh"
#include "vta/vta.hh"
#include "vta/vta_const.hh"

namespace gem5
{

class InstructionFetchModule : public SimObject
{
  private:
    size_t pc{};
    vta::Instruction instruction;

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
            delete pkt;
            DPRINTF(BaseVTAFlag, "Instruction: %016lx%016lx\n",
                *(uint64_t *)&owner.instruction.data[8],
                *(uint64_t *)&owner.instruction.data[0]);
            DPRINTF(
                BaseVTAFlag, "Opcode: %d\n", (int)owner.instruction.opcode());
            owner.schedule(owner.event, curTick());
            DPRINTF(BaseVTAFlag, "Instruction fetch event scheduled\n");
            return true;
        }

        auto
        recvReqRetry() -> void override
        {}

        auto
        sendRetryResp() -> void override
        {}
    } instruction_port;

    CommandQueue &loadCommandQueue;
    CommandQueue &computeCommandQueue;
    CommandQueue &storeCommandQueue;

    class ProgressEvent : public Event
    {
      private:
        InstructionFetchModule &owner;

      public:
        ProgressEvent(InstructionFetchModule &owner) : owner{owner} {}

        auto
        process() -> void override
        {
            static enum class State {
                FETCH,
                DECODE,
                LOAD,
                COMPUTE,
                STORE,
            } state{};
            switch (state) {
            case State::FETCH: {
                DPRINTF(BaseVTAFlag, "Fetch\n");
                const auto req{std::make_shared<Request>(Addr{owner.pc},
                    sizeof(vta::Instruction), Request::INST_FETCH, 3)};
                auto packet{new Packet{req, MemCmd::ReadReq}};
                DPRINTF(BaseVTAFlag, "Packet: %s\n", packet->print());
                packet->dataStatic(&owner.instruction);
                const auto ret{owner.instruction_port.sendTimingReq(packet)};
                assert(ret);
                state = State::DECODE;
                return;
            }
            case State::DECODE: {
                DPRINTF(BaseVTAFlag, "Decode\n");
                owner.pc += sizeof(vta::Instruction);
                const auto instruction{owner.instruction};
                const auto opcode{instruction.opcode()};
                switch (opcode) {
                case vta::Opcode::LOAD:
                    if (const auto memory_type{
                            instruction.asMemoryInstruction().memory_type};
                        memory_type == vta::MemoryId::INPUT ||
                        memory_type == vta::MemoryId::WEIGHT) {
                        state = State::LOAD;
                    } else {
                        state = State::COMPUTE;
                    }
                    break;
                case vta::Opcode::STORE:
                    state = State::STORE;
                    break;
                case vta::Opcode::FINISH:
                    DPRINTF(BaseVTAFlag, "Finish\n");
                    return;
                default:
                    state = State::COMPUTE;
                    break;
                }
                process();
                return;
            }
            case State::LOAD:
                DPRINTF(BaseVTAFlag, "Load\n");
                if (!owner.loadCommandQueue.full()) {
                    owner.loadCommandQueue.push(owner.instruction);
                    state = State::FETCH;
                }
                break;
            case State::COMPUTE:
                DPRINTF(BaseVTAFlag, "Compute\n");
                if (!owner.computeCommandQueue.full()) {
                    owner.computeCommandQueue.push(owner.instruction);
                    state = State::FETCH;
                }
                break;
            case State::STORE:
                DPRINTF(BaseVTAFlag, "Store\n");
                if (!owner.storeCommandQueue.full()) {
                    owner.storeCommandQueue.push(owner.instruction);
                    state = State::FETCH;
                }
                break;
            }
            owner.schedule(owner.event, curTick() + 1);
        }
    } event{*this};

  public:
    PARAMS(InstructionFetchModule);

    InstructionFetchModule(const Params &params) :
        SimObject{params},
        instruction_port{params.name + ".instruction_port", *this},
        loadCommandQueue{*params.load_command_queue},
        computeCommandQueue{*params.compute_command_queue},
        storeCommandQueue{*params.store_command_queue}
    {}

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
