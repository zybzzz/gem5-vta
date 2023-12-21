#ifndef VTA_HH_
#define VTA_HH_

#include <array>
#include <cstdint>

#include "vta/bit_cast.hh"
#include "vta/stream.hh"
#include "vta/vta_const.hh"
#include "vta/vta_hw_config.hh"

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

        operator Instruction() const noexcept
        {
            return bit_cast<Instruction>(*this);
        }
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

        operator Instruction() const noexcept
        {
            return bit_cast<Instruction>(*this);
        }
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

        operator Instruction() const noexcept
        {
            return bit_cast<Instruction>(*this);
        }
    };

    operator MemoryInstruction() const noexcept
    {
        return bit_cast<MemoryInstruction>(*this);
    }

    operator GemmInstruction() const noexcept
    {
        return bit_cast<GemmInstruction>(*this);
    }

    operator AluInstruction() const noexcept
    {
        return bit_cast<AluInstruction>(*this);
    }

    auto
    opcode() const noexcept -> Opcode
    {
        return static_cast<Opcode>(data.front());
    }

    auto
    asMemoryInstruction() const noexcept -> MemoryInstruction
    {
        return *this;
    }

    auto
    asGemmInstruction() const noexcept -> GemmInstruction
    {
        return *this;
    }

    auto
    asAluInstruction() const noexcept -> AluInstruction
    {
        return *this;
    }

    enum class InstructionType
    {
        None, // indicate union is nullptr
        MemoryInstruction,
        GemmInstruction,
        AluInstruction,
    };
};

using BusType = std::array<uint8_t, BUS_WIDTH / 8>;

using CommandQueue = Stream<Instruction, STREAM_IN_DEPTH>;
using DependencyQueue = Stream<Instruction, STREAM_IN_DEPTH>;

using InputBuffer =
    std::array<std::array<BusType, INPUT_MATRIX_RATIO>, INPUT_BUFFER_DEPTH>;
using WeightBuffer =
    std::array<std::array<BusType, WEIGHT_MATRIX_RATIO>, WEIGHT_BUFFER_DEPTH>;
using OutputBuffer =
    std::array<std::array<BusType, OUTPUT_MATRIX_RATIO>, OUTPUT_BUFFER_DEPTH>;

} // namespace vta

#endif
