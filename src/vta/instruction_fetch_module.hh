#ifndef INSTRUCTION_FETCH_MODULE_HH
#define INSTRUCTION_FETCH_MODULE_HH

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>
#include <string_view>

#include "base/logging.hh"
#include "base/trace.hh"
#include "base/types.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/packet.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/InstructionFetchModule.hh"
#include "sim/cur_tick.hh"
#include "sim/sim_object.hh"
#include "vta/queue/command_queue.hh"
#include "vta/vta.hh"

using namespace std::literals;

namespace gem5
{

class InstructionFetchModule : public SimObject
{
  private:
    size_t pc{};
    vta::Instruction instruction;

    RequestorID id;
    bool finish_{};
    Event *finishEvent_;

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
        virtual auto
        recvTimingResp(PacketPtr pkt) -> bool override
        {
            delete pkt;
            DPRINTF(BaseVTAFlag, "Instruction: %s\n", owner.instruction);
            owner.schedule(owner.event, curTick());
            return true;
        }

        virtual auto
        recvReqRetry() -> void override
        {
            owner.schedule(owner.event, curTick());
        }

        virtual auto
        sendRetryResp() -> void override
        {
            panic("Unreachable\n");
        }
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

        virtual auto
        process() -> void override
        {
            static enum class State {
                FETCH,
                DECODE,
                LOAD,
                COMPUTE,
                STORE,
                FINISH_LOAD,
                FINISH_COMPUTE,
                FINISH_STORE,
                FINISH,
            } state{};

            switch (state) {
            case State::FETCH: {
                DPRINTF(BaseVTAFlag, "Fetch\n");
                const auto req{std::make_shared<Request>(Addr{owner.pc},
                    sizeof(vta::Instruction),
                    Request::INST_FETCH | Request::PHYSICAL, owner.id)};
                auto *const packet{new Packet{req, MemCmd::ReadReq}};
                DPRINTF(BaseVTAFlag, "Packet: %s\n", packet->print());
                packet->dataStatic(&owner.instruction);
                if (const auto ret{
                        owner.instruction_port.sendTimingReq(packet)};
                    !ret) {
                    delete packet;
                    break;
                }
                state = State::DECODE;
                break;
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
                    state = State::FINISH_LOAD;
                    break;
                case vta::Opcode::GEMM:
                case vta::Opcode::ALU:
                    state = State::COMPUTE;
                    break;
                default:
                    panic("Illegal instruction %s at pc 0x%016lx\n",
                        owner.instruction, owner.pc);
                }
                process();
                break;
            }
            case State::LOAD:
                DPRINTF(BaseVTAFlag, "Load\n");
                owner.loadCommandQueue.write(owner.instruction);
                state = State::FETCH;
                break;
            case State::COMPUTE:
                DPRINTF(BaseVTAFlag, "Compute\n");
                owner.computeCommandQueue.write(owner.instruction);
                state = State::FETCH;
                break;
            case State::STORE:
                DPRINTF(BaseVTAFlag, "Store\n");
                owner.storeCommandQueue.write(owner.instruction);
                state = State::FETCH;
                break;
            case State::FINISH_LOAD:
                owner.loadCommandQueue.write(owner.instruction);
                state = State::FINISH_COMPUTE;
                break;
            case State::FINISH_COMPUTE:
                owner.computeCommandQueue.write(owner.instruction);
                state = State::FINISH_STORE;
                break;
            case State::FINISH_STORE:
                owner.storeCommandQueue.write(owner.instruction);
                state = State::FINISH;
                break;
            case State::FINISH:
                if (owner.finish()) {
                    panic("Finished\n");
                }
                owner.finish() = true;
                owner.schedule(owner.finishEvent(), curTick());
                break;
            }
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

    virtual auto
    init() -> void override
    {
        loadCommandQueue.producerEvent = &event;
        computeCommandQueue.producerEvent = &event;
        storeCommandQueue.producerEvent = &event;
    }

    virtual auto
    startup() -> void override
    {
        schedule(event, curTick());
    }

    virtual auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == "instruction_port"sv) {
            return instruction_port;
        }
        return SimObject::getPort(if_name, idx);
    }

    constexpr auto
    requestorId() noexcept -> RequestorID &
    {
        return id;
    }

    constexpr auto
    finish() -> bool &
    {
        return finish_;
    }

    constexpr auto
    finishEvent() noexcept -> Event *&
    {
        return finishEvent_;
    }
};

} // namespace gem5

#endif
