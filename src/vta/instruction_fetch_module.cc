#include "vta/instruction_fetch_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "vta/vta.hh"
#include "vta/vta_const.hh"

namespace gem5
{
InstructionFetchModule::InstructionFetchModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    computeCommandQueue(params.compute_command_queue),
    storeCommandQueue(params.store_command_queue)
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
} // namespace gem5
