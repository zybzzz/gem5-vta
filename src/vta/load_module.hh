#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/LoadModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer/input_buffer.hh"
#include "vta/buffer/weight_buffer.hh"
#include "vta/queue/command_queue.hh"
#include "vta/queue/dependency_queue.hh"

using namespace std::literals;

namespace gem5
{

class LoadModule : public SimObject
{
  private:
    vta::MemoryInstruction instruction;

    RequestorID id;
    bool finish_{};
    Event *finishEvent_;

    // from mem
    class DataPort : public RequestPort
    {
      private:
        LoadModule &owner;

      public:
        DataPort(const std::string_view name, LoadModule &owner) :
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
        {}

        virtual auto
        sendRetryResp() -> void override
        {}
    } data_port;

    CommandQueue &loadCommandQueue;

    DependencyQueue &loadToComputeQueue;
    DependencyQueue &computeToLoadQueue;

    InputBuffer &inputBuffer;
    WeightBuffer &weightBuffer;

    class LoadModuleWorkingEvent : public Event
    {
      private:
        LoadModule &owner;

        void
        resetMem(size_t &sram_idx, size_t range)
        {
            for (int i{}; i < range; ++i) {
                for (int j{}; j < vta::INPUT_MATRIX_RATIO; ++j) {
                    memset(
                        static_cast<void *>(&(owner.inputBuffer[sram_idx][0])),
                        0, vta::INPUT_MATRIX_RATIO);
                }
                ++sram_idx;
            }

            return;
        }

      public:
        LoadModuleWorkingEvent(LoadModule &owner) : owner(owner) {}

        virtual auto
        process() -> void override
        {
            static enum class State {
                FETCH,
                DECODE,
                READ_COMPUTE_TO_LOAD_QUEUE,
                MEMORY_READ_AND_DISPATCH_TO_BUFFER,
                WRITE_LOAD_TO_COMPUTER_QUEUE,
                FINISH
            } state{State::FETCH};

            static vta::MemoryInstruction instruction;

            switch (state) {
            case State::FETCH:
                state = State::DECODE;
                owner.loadCommandQueue.read();
                break;
            case State::DECODE:
                instruction = static_cast<vta::MemoryInstruction>(
                    owner.loadCommandQueue.read_buf);
                if (instruction.opcode == vta::Opcode::FINISH) {
                    state = State::FINISH;
                    owner.schedule(this, curTick());
                    break;
                }
                state = State::READ_COMPUTE_TO_LOAD_QUEUE;
                owner.schedule(this, curTick());
                break;
            case State::READ_COMPUTE_TO_LOAD_QUEUE:
                state = State::MEMORY_READ_AND_DISPATCH_TO_BUFFER;
                if (instruction.pop_next_dependence) {
                    owner.computeToLoadQueue.read();
                    break;
                }
                owner.schedule(this, curTick());
                break;
            case State::MEMORY_READ_AND_DISPATCH_TO_BUFFER: {
                size_t x_width{static_cast<size_t>(instruction.x_pad_0 +
                                                   instruction.x_size +
                                                   instruction.x_pad_1)};
                size_t y_offset_0{
                    static_cast<size_t>(x_width * instruction.y_pad_0)};
                size_t y_offset_1{
                    static_cast<size_t>(x_width * instruction.y_pad_1)};
                size_t sram_idx{static_cast<size_t>(instruction.sram_base)};
                size_t dram_idx{static_cast<size_t>(instruction.dram_base)};

                if (instruction.memory_type == vta::MemoryId::INPUT) {
                    // load pad 2d
                    resetMem(sram_idx, y_offset_0);
                    for (int y{}; y < instruction.y_size; ++y) {
                        resetMem(sram_idx, instruction.x_pad_0);

                        const auto req{std::make_shared<Request>(
                            Addr{dram_idx * vta::INPUT_MATRIX_RATIO},
                            instruction.x_size * vta::INPUT_BUFFER_SIZE,
                            Request::PHYSICAL, owner.id)};
                        auto *const packet{new Packet{req, MemCmd::ReadReq}};
                        packet->dataStaticConst(
                            owner.inputBuffer[sram_idx][0].data());
                        const auto ret{owner.data_port.sendTimingReq(packet)};
                        assert(ret);

                        sram_idx += instruction.x_size;
                        dram_idx += instruction.x_stride;
                    }
                    resetMem(sram_idx, y_offset_1);
                } else if (instruction.memory_type == vta::MemoryId::WEIGHT) {
                    // load 2d
                    for (int y{}; y < instruction.y_size; ++y) {
                        const auto req{std::make_shared<Request>(
                            Addr{dram_idx * vta::WEIGHT_MATRIX_RATIO},
                            instruction.x_size * vta::WEIGHT_BUFFER_SIZE,
                            Request::PHYSICAL, owner.id)};
                        auto *const packet{new Packet{req, MemCmd::ReadReq}};
                        packet->dataStaticConst(
                            owner.weightBuffer[sram_idx][0].data());
                        const auto ret{owner.data_port.sendTimingReq(packet)};
                        assert(ret);

                        sram_idx += instruction.x_size;
                        dram_idx += instruction.x_stride;
                    }
                } else {
                    panic("invalid memory id\n");
                }
                state = State::WRITE_LOAD_TO_COMPUTER_QUEUE;
                owner.schedule(this, curTick());
                break;
            }
            case State::WRITE_LOAD_TO_COMPUTER_QUEUE:
                state = State::FETCH;
                if (instruction.push_next_dependence) {
                    owner.loadToComputeQueue.write(true);
                    break;
                }
                owner.schedule(this, curTick());
                break;
            case State::FINISH:
                if (owner.finish()) {
                    panic("Finished\n");
                }
                owner.finish_ = true;
                owner.schedule(owner.finishEvent(), curTick());
                break;
            }
        }
    } workingEvent{*this};

  public:
    PARAMS(LoadModule);

    LoadModule(const Params &params) :
        SimObject{params},
        data_port{params.name + ".load_data_port", *this},
        loadCommandQueue{*params.load_command_queue},
        loadToComputeQueue{*params.load_to_compute_queue},
        computeToLoadQueue{*params.compute_to_load_queue},
        inputBuffer{*params.input_buffer},
        weightBuffer{*params.weight_buffer}
    {}

    virtual auto
    init() -> void override
    {
        // some func in command queue
        loadCommandQueue.consumerEvent = &workingEvent;

        loadToComputeQueue.producerEvent = &workingEvent;
        computeToLoadQueue.consumerEvent = &workingEvent;
    }

    virtual auto
    startup() -> void override
    {
        schedule(workingEvent, curTick());
    }

    virtual auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == "load_data_port"sv) {
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
