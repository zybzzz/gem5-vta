#ifndef VTA_HH_
#define VTA_HH_

#include <array>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <ostream>

#include "vta/bit_cast.hh"
#include "vta/stream.hh"
#include "vta/vta_const.hh"
#include "vta/vta_hw_config.hh"

namespace vta
{

#pragma pack(1)
struct Instruction
{
    std::array<uint8_t, INSTRUCTION_WIDTH / 8> data;

    struct CommonInstruction
    {
        Opcode opcode : OPCODE_BIT_WIDTH;
        uint64_t pop_prev_dependence : 1;
        uint64_t pop_next_dependence : 1;
        uint64_t push_prev_dependence : 1;
        uint64_t push_next_dependence : 1;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 4;
        uint64_t : 64;

        operator Instruction() const noexcept
        {
            return bit_cast<Instruction>(*this);
        }
    };

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

    constexpr
    operator MemoryInstruction() const noexcept
    {
        return bit_cast<MemoryInstruction>(*this);
    }

    constexpr
    operator GemmInstruction() const noexcept
    {
        return bit_cast<GemmInstruction>(*this);
    }

    constexpr
    operator AluInstruction() const noexcept
    {
        return bit_cast<AluInstruction>(*this);
    }

    constexpr auto
    opcode() const noexcept -> Opcode
    {
        return bit_cast<CommonInstruction>(*this).opcode;
    }

    constexpr auto
    asMemoryInstruction() const noexcept -> MemoryInstruction
    {
        return *this;
    }

    constexpr auto
    asGemmInstruction() const noexcept -> GemmInstruction
    {
        return *this;
    }

    constexpr auto
    asAluInstruction() const noexcept -> AluInstruction
    {
        return *this;
    }

    friend auto
    operator<<(
        std::ostream &os, const Instruction &instruction) -> std::ostream &
    {
        const auto flags{os.flags()};
        const auto fill{os.fill('0')};
        const auto [low, high]{bit_cast<std::array<uint64_t, 2>>(instruction)};
        os << "0x" << std::hex << std::setw(16) << high << std::setw(16)
           << low;
        os.flags(flags);
        os.fill(fill);
        return os;
    }
};

#pragma pack()

using BusType = std::array<uint8_t, BUS_WIDTH / 8>;

using CommandQueue = Stream<Instruction, STREAM_IN_DEPTH>;
using DependencyQueue = Stream<bool, STREAM_IN_DEPTH>;

using InputBuffer =
    std::array<std::array<BusType, INPUT_MATRIX_RATIO>, INPUT_BUFFER_DEPTH>;
using WeightBuffer =
    std::array<std::array<BusType, WEIGHT_MATRIX_RATIO>, WEIGHT_BUFFER_DEPTH>;
using OutputBuffer =
    std::array<std::array<BusType, OUTPUT_MATRIX_RATIO>, OUTPUT_BUFFER_DEPTH>;

} // namespace vta

#endif
