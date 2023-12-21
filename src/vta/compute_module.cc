#include "vta/compute_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
ComputeModule::ComputeModuleWorkingEvent::ComputeModuleWorkingEvent(
    gem5::ComputeModule *computeModule) :
    computeModule(computeModule),
    loadToComputeQueueReadFlag(false),
    storeToComputeQueueReadFlag(false),
    computeToLoadQueueWriteFlag(false),
    computeToStoreQueueWriteFlag(false)
{}

auto
ComputeModule::ComputeModuleWorkingEvent::clearFlag() noexcept -> void
{
    loadToComputeQueueReadFlag = false;
    storeToComputeQueueReadFlag = false;
    computeToLoadQueueWriteFlag = false;
    computeToStoreQueueWriteFlag = false;
}

auto
ComputeModule::ComputeModuleWorkingEvent::process() -> void
{
    while (computeModule->instructionType == InstructionType::None ||
           !computeModule->computeCommandQueue->empty()) {
        switch (computeModule->status) {
        case ComputeModuleStatus::WaitToRead:
            if (computeModule->instructionType ==
                vta::Instruction::InstructionType::None) {
                // get instruction from queue
            }

            if (/*insn.pop_prev_dep*/ true && !loadToComputeQueueReadFlag) {
                if (computeModule->loadToComputeQueue->tryPop()) {
                    loadToComputeQueueReadFlag = true;
                } else {
                    computeModule->reschedule(this, curTick() + 1);
                    return;
                }
            }
            if (/*insn.pop_prev_dep*/ true && !storeToComputeQueueReadFlag) {
                if (computeModule->computeToStoreQueue->tryPop()) {
                    storeToComputeQueueReadFlag = true;
                    computeModule->status = ComputeModuleStatus::Normal;
                } else {
                    computeModule->reschedule(this, curTick() + 1);
                    return;
                }
            }

            break;
        case ComputeModuleStatus::Normal:
            // do computer
            switch (computeModule->instructionType) {
            case InstructionType::MemoryInstruction:
                // do mem instruction
                break;
            case InstructionType::AluInstruction:
                // do alu instruction
                break;
            case InstructionType::GemmInstruction:
                // do gemm instruction
                break;
            default:;
            }
            break;
        case ComputeModuleStatus::WaitToWrite:
            if (/*insn.push_prev_dep*/ true && !computeToLoadQueueWriteFlag) {
                if (computeModule->storeToComputeQueue->tryPush()) {
                    computeToLoadQueueWriteFlag = true;
                    // free instruction
                } else {
                    computeModule->status = ComputeModuleStatus::WaitToWrite;
                    computeModule->reschedule(this, curTick() + 1);
                }
            }

            if (/*insn.push_prev_dep*/ true && !computeToStoreQueueWriteFlag) {
                if (computeModule->storeToComputeQueue->tryPush()) {
                    computeToStoreQueueWriteFlag = true;
                    computeModule->status = ComputeModuleStatus::WaitToRead;
                    // free instruction
                } else {
                    computeModule->status = ComputeModuleStatus::WaitToWrite;
                    computeModule->reschedule(this, curTick() + 1);
                }
            }

            clearFlag();
            break;
        }
    }
}

ComputeModule::ComputeModule(const Params &params) :
    SimObject(params),
    computeCommandQueue(params.compute_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer),
    status(ComputeModuleStatus::WaitToRead),
    workingEvent(this),
    instructionType(InstructionType::None),
    instruction{nullptr}
{
    DPRINTF(BaseVTAFlag, "create ComputeModule!\n");
}
} // namespace gem5
