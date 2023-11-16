#ifndef VTA_HH_
#define VTA_HH_

#include <array>
#include <cstdint>

#include "vta/bit_cast.hh"
#include "vta/vta_const.hh"

namespace vta
{
struct Instruction
{
    std::array<uint8_t, INSTRUCTION_WIDTH> data;

    struct MemoryInstruction
    {
        Opcode opcode : OPCODE_BIT_WIDTH;
        uint64_t : 1;
        uint64_t pop_next_dependence : 1;
        uint64_t : 1;
        uint64_t push_next_dependence : 1;
        MemoryId memory_type : MEM_OP_ID_BIT_WIDTH;
        uint64_t sram_base : MEM_OP_SRAM_ADDR_BIT_WIDTH;
        uint64_t dram_base : MEM_OP_DRAM_ADDR_BIT_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 4 - MEM_OP_ID_BIT_WIDTH -
            MEM_OP_SRAM_ADDR_BIT_WIDTH - MEM_OP_DRAM_ADDR_BIT_WIDTH;
        uint64_t y_size : MEM_OP_SIZE_BIT_WIDTH;
        uint64_t x_size : MEM_OP_SIZE_BIT_WIDTH;
        uint64_t x_stride : MEM_OP_STRIDE_BIT_WIDTH;
        uint64_t y_pad_0 : MEM_OP_PAD_BIT_WIDTH;
        uint64_t y_pad_1 : MEM_OP_PAD_BIT_WIDTH;
        uint64_t x_pad_0 : MEM_OP_PAD_BIT_WIDTH;
        uint64_t x_pad_1 : MEM_OP_PAD_BIT_WIDTH;
        uint64_t : 64 - 2 * MEM_OP_SIZE_BIT_WIDTH - MEM_OP_STRIDE_BIT_WIDTH -
            4 * MEM_OP_PAD_BIT_WIDTH;
    };

    struct GemmInstruction
    {
        Opcode opcode : OPCODE_BIT_WIDTH;
        uint64_t pop_prev_dependence : 1;
        uint64_t pop_next_dependence : 1;
        uint64_t push_prev_dependence : 1;
        uint64_t push_next_dependence : 1;
        uint64_t reset_reg : 1;
        uint64_t micro_op_begin : LOG_MICRO_OP_BUFFER_DEPTH;
        uint64_t micro_op_end : LOG_MICRO_OP_BUFFER_DEPTH + 1;
        uint64_t iter_outer : LOOP_ITER_WIDTH;
        uint64_t iter_inner : LOOP_ITER_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 6 - 2 * LOG_MICRO_OP_BUFFER_DEPTH -
            2 * LOOP_ITER_WIDTH;
        uint64_t accumulator_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        uint64_t accumulator_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        uint64_t input_factor_in : LOG_INPUT_BUFFER_DEPTH;
        uint64_t input_factor_out : LOG_INPUT_BUFFER_DEPTH;
        uint64_t weight_factor_in : LOG_WEIGHT_BUFFER_DEPTH;
        uint64_t weight_factor_out : LOG_WEIGHT_BUFFER_DEPTH;
        uint64_t : 64 - 2 * LOG_ACCUMULATOR_BUFFER_DEPTH -
            2 * LOG_INPUT_BUFFER_DEPTH - 2 * LOG_WEIGHT_BUFFER_DEPTH;
    };

    struct AluInstruction
    {
        Opcode opcode : OPCODE_BIT_WIDTH;
        uint64_t pop_prev_dependence : 1;
        uint64_t pop_next_dependence : 1;
        uint64_t push_prev_dependence : 1;
        uint64_t push_next_dependence : 1;
        uint64_t reset_reg : 1;
        uint64_t micro_op_begin : LOG_MICRO_OP_BUFFER_DEPTH;
        uint64_t micro_op_end : LOG_MICRO_OP_BUFFER_DEPTH + 1;
        uint64_t iter_outer : LOOP_ITER_WIDTH;
        uint64_t iter_inner : LOOP_ITER_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 6 - 2 * LOG_MICRO_OP_BUFFER_DEPTH -
            2 * LOOP_ITER_WIDTH;
        uint64_t dst_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        uint64_t dst_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        uint64_t src_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        uint64_t src_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        AluOpcode alu_opcode : ALU_OPCODE_BIT_WIDTH;
        uint64_t use_imm : 1;
        int64_t imm : ALU_OP_IMMEDIATE_BIT_WIDTH;
        uint64_t : 64 - 4 * LOG_ACCUMULATOR_BUFFER_DEPTH -
            ALU_OPCODE_BIT_WIDTH - 1 - ALU_OP_IMMEDIATE_BIT_WIDTH;
    };

    auto
    opcode() const noexcept -> Opcode
    {
        return static_cast<Opcode>(data.front());
    }

    auto
    as_memory() const noexcept -> MemoryInstruction
    {
        return bit_cast<MemoryInstruction>(*this);
    }

    auto
    as_gemm() const noexcept -> GemmInstruction
    {
        return bit_cast<GemmInstruction>(*this);
    }

    auto
    as_alu() const noexcept -> AluInstruction
    {
        return bit_cast<AluInstruction>(*this);
    }
};
} // namespace vta

#endif
