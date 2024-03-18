#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/LoadModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/command_queue.hh"
#include "vta/dependency_queue.hh"

namespace gem5
{

class LoadModule : public SimObject
{
  private:
    vta::MemoryInstruction instruction;

    bool lastInstructionFinish{true};

    CommandQueue &loadCommandQueue;

    DependencyQueue &loadToComputeQueue;
    DependencyQueue &computeToLoadQueue;

    Buffer &inputBuffer;
    Buffer &weightBuffer;

    class LoadModuleWorkingEvent : public Event
    {
      private:
        LoadModule &owner;

      public:
        LoadModuleWorkingEvent(LoadModule &owner) : owner(owner) {}

        auto
        process() -> void override
        {
            static enum class Status {
                Normal,
                WaitToRead,
                WaitToWrite,
            } status{Status::WaitToRead};
            /* while (!owner.lastInstructionFinish ||
                   !owner.loadCommandQueue.empty()) {
                switch (status) {
                case Status::WaitToRead:
                    if (owner.lastInstructionFinish) {
                        // get instruction from queue
                        auto tickStruct = owner.loadCommandQueue.pop();
                        owner.instruction =
                            tickStruct.value.asMemoryInstruction();
                        owner.fetchInstTime = tickStruct.time;
                        owner.lastInstructionFinish = false;
                    }
                    if (owner.instruction.pop_next_dependence) {
                        // check instruction flag then maybe read flag from
                        // data queue if queue can't read, delay to next time
                        if (owner.computeToLoadQueue.tryPop()) {
                            status = Status::Normal;
                        } else {
                            owner.reschedule(this, curTick() + 1);
                            return; // return to wait next
                        }
                    }

                    break;
                case Status::Normal:
                    // judge and do load
                    break;
                case Status::WaitToWrite:
                    if (owner.instruction.push_next_dependence) {
                        if (owner.loadToComputeQueue.tryPush()) {
                            status = Status::WaitToRead;
                            owner.lastInstructionFinish = true;
                        } else {
                            // check instruction flag then maybe write flag
                            // from data queue if queue can't read, delay to
                            // next time
                            status = Status::WaitToWrite;
                            owner.reschedule(this, curTick() + 1);
                            return; // return to wait next
                        }
                    }
                    break;
                }
            } */

            owner.reschedule(this, curTick() + 1);
        }
    } workingEvent{*this};

  public:
    PARAMS(LoadModule);

    LoadModule(const Params &params) :
        SimObject{params},
        loadCommandQueue{*params.load_command_queue},
        loadToComputeQueue{*params.load_to_compute_queue},
        computeToLoadQueue{*params.compute_to_load_queue},
        inputBuffer{*params.input_buffer},
        weightBuffer{*params.weight_buffer}
    {}

    virtual auto
    startup() -> void override
    {
        schedule(workingEvent, curTick());
    }
};

} // namespace gem5

#endif
