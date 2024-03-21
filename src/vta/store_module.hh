#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include <cstring>
#include <memory>
#include <string>
#include <string_view>

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/StoreModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer/output_buffer.hh"
#include "vta/queue/command_queue.hh"
#include "vta/queue/dependency_queue.hh"
#include "vta/vta.hh"
#include "vta/vta_const.hh"

using namespace std::literals;

namespace gem5
{

class StoreModule : public SimObject
{
  private:
    RequestorID id;
    bool finish_{};
    Event *finishEvent_;

    class DataPort : public RequestPort
    {
      private:
        StoreModule &owner;

      public:
        DataPort(const std::string_view name, StoreModule &owner) :
            RequestPort{std::string{name}}, owner{owner}
        {}

      protected:
        virtual auto
        recvTimingResp(PacketPtr pkt) -> bool override
        {
            delete pkt;
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
    } data_port;

    CommandQueue &storeCommandQueue;

    DependencyQueue &computeToStoreQueue;
    DependencyQueue &storeToComputeQueue;

    OutputBuffer &outputBuffer;

    class ProcessEvent : public Event
    {
      private:
        StoreModule &owner;

      public:
        ProcessEvent(StoreModule &owner) : owner{owner} {}

        virtual auto
        process() -> void override
        {
            static enum class State {
                FETCH,
                DECODE,
                READ_COMPUTE_TO_STORE_QUEUE,
                WRITE_MEMORY,
                WRITE_STORE_TO_COMPUTE_QUEUE,
                FINISH,
            } state{};
            static vta::MemoryInstruction instruction;
            static size_t y;
            static vta::SramAddr sramAddr;
            static vta::DramAddr dramAddr;

            switch (state) {
            case State::FETCH:
                owner.storeCommandQueue.read();
                state = State::DECODE;
                break;
            case State::DECODE:
                instruction = owner.storeCommandQueue.read_buf;
                if (instruction.opcode == vta::Opcode::FINISH) {
                    state = State::FINISH;
                    process();
                    break;
                }
                state = State::READ_COMPUTE_TO_STORE_QUEUE;
                break;
            case State::READ_COMPUTE_TO_STORE_QUEUE:
                y = 0;
                sramAddr = instruction.sram_base;
                dramAddr = instruction.dram_base;
                state = State::WRITE_MEMORY;
                if (instruction.pop_prev_dependence) {
                    owner.computeToStoreQueue.read();
                } else {
                    process();
                }
                break;
            case State::WRITE_MEMORY: {
                const auto req{std::make_shared<Request>(
                    Addr{dramAddr * vta::OUTPUT_MATRIX_RATIO},
                    instruction.x_size * vta::OUTPUT_MATRIX_SIZE,
                    Request::PHYSICAL, owner.id)};
                auto *const packet{new Packet{req, MemCmd::WriteReq}};
                packet->dataStaticConst(
                    owner.outputBuffer[sramAddr][0].data());
                if (const auto ret{owner.data_port.sendTimingReq(packet)};
                    !ret) {
                    delete packet;
                    break;
                }

                ++y;
                sramAddr += instruction.x_size;
                dramAddr += instruction.x_stride;
                if (y == instruction.y_size) {
                    state = State::WRITE_STORE_TO_COMPUTE_QUEUE;
                }
                break;
            }
            case State::WRITE_STORE_TO_COMPUTE_QUEUE:
                state = State::FETCH;
                if (instruction.push_prev_dependence) {
                    owner.storeToComputeQueue.write(true);
                } else {
                    process();
                }
                break;
            case State::FINISH:
                if (owner.finish()) {
                    panic("Finished\n");
                }
                owner.finish_ = true;
                owner.schedule(owner.finishEvent(), curTick());
                break;
            }
        };
    } event{*this};

  public:
    PARAMS(StoreModule);

    StoreModule(const Params &params) :
        SimObject{params},
        data_port{params.name + ".store_data_port", *this},
        storeCommandQueue{*params.store_command_queue},
        computeToStoreQueue{*params.compute_to_store_queue},
        storeToComputeQueue{*params.store_to_compute_queue},
        outputBuffer{*params.output_buffer}
    {}

    virtual auto
    init() -> void override
    {
        storeCommandQueue.consumerEvent = &event;

        computeToStoreQueue.consumerEvent = &event;
        storeToComputeQueue.producerEvent = &event;
    }

    virtual auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == "store_data_port"sv) {
            return data_port;
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
