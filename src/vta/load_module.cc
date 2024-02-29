#include "vta/load_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadModule::LoadModuleWorkingEvent::LoadModuleWorkingEvent(
    gem5::LoadModule *loadModule) :
    loadModule(loadModule)
{}

auto
LoadModule::startup() -> void
{
    this->schedule(workingEvent, curTick() + uint64_t(pollingLatency));
}

auto
LoadModule::LoadModuleWorkingEvent::process() -> void
{
    while (!loadModule->lastInstructionFinish ||
           !loadModule->loadCommandQueue->empty()) {
        switch (loadModule->status) {
        case LoadModuleStatus::WaitToRead:
            if (loadModule->lastInstructionFinish) {
                // get instruction from queue
                auto tickStruct = loadModule->loadCommandQueue->pop();
                loadModule->instruction =
                    tickStruct.value.asMemoryInstruction();
                loadModule->fetchInstTime = tickStruct.time;
                loadModule->lastInstructionFinish = false;
            }
            if (loadModule->instruction.pop_next_dependence) {
                // check instruction flag then maybe read flag from data queue
                // if queue can't read, delay to next time
                if (loadModule->computeToLoadQueue->tryPop()) {
                    loadModule->status = LoadModuleStatus::Normal;
                } else {
                    loadModule->reschedule(this,
                        curTick() +
                            uint64_t(loadModule->waitDataQueueReadLatency));
                    return; // return to wait next
                }
            }

            break;
        case LoadModuleStatus::Normal:
            // judge and do load
            break;
        case LoadModuleStatus::WaitToWrite:
            if (loadModule->instruction.push_next_dependence) {
                if (loadModule->loadToComputeQueue->tryPush()) {
                    loadModule->status = LoadModuleStatus::WaitToRead;
                    loadModule->lastInstructionFinish = true;
                } else {
                    // check instruction flag then maybe write flag from data
                    // queue if queue can't read, delay to next time
                    loadModule->status = LoadModuleStatus::WaitToWrite;
                    loadModule->reschedule(this,
                        curTick() +
                            uint64_t(loadModule->waitDataQueueWriteLatency));
                    return; // return to wait next
                }
            }
            break;
        }
    }

    loadModule->reschedule(
        this, curTick() + uint64_t(loadModule->pollingLatency));

    return;
}

LoadModule::LoadModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    status(LoadModuleStatus::WaitToRead),
    workingEvent(this),
    pollingLatency(params.polling_latency),
    lastInstructionFinish(true),
    waitDataQueueReadLatency(params.wait_dataqueue_read_latency),
    waitDataQueueWriteLatency(params.wait_dataqueue_write_latency)
{
    DPRINTF(BaseVTAFlag, "create LoadModule!\n");
}
} // namespace gem5
