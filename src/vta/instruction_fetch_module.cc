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
            } else {
                DPRINTF(BaseVTAFlag, "instruction to compute\n");
                // computeCommandQueue << instruction;
            }
            break;
        case vta::Opcode::STORE:
            DPRINTF(BaseVTAFlag, "instruction to store\n");
            // storeCommandQueue << instruction;
            break;
        default:
            DPRINTF(BaseVTAFlag, "instruction to compute\n");
            // computeCommandQueue << instruction;
            break;
        }
    }
}
} // namespace gem5
