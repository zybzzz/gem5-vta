#ifndef VTA_HH_
#define VTA_HH_

#include <array>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <ostream>

#include "vta/bit_cast.hh"
#include "vta/vta_const.hh"
#include "vta/vta_int.hh"

namespace vta
{
using Bus = Unsigned<BUS_WIDTH>;
using MicroOp = Unsigned<MICRO_OP_WIDTH>;
using Input = Signed<INPUT_WIDTH>;
using Weight = Signed<WEIGHT_WIDTH>;
using Output = Signed<OUTPUT_WIDTH>;
using Accumulator = Signed<ACCUMULATOR_WIDTH>;
using Multiplier = Signed<WEIGHT_WIDTH + INPUT_WIDTH + 1>;
using Sum = Signed<WEIGHT_WIDTH + INPUT_WIDTH + LOG_BLOCK_IN + 1>;

enum class Opcode : Unsigned<ALU_OPCODE_BIT_WIDTH>
{
    LOAD = 0,
    STORE = 1,
    GEMM = 2,
    FINISH = 3,
    ALU = 4,
};
using InstructionData = Unsigned<INSTRUCTION_WIDTH>;

enum class MemoryId : Unsigned<MEM_OP_ID_BIT_WIDTH>
{
    MICRO_OP = 0,
    WEIGHT = 1,
    INPUT = 2,
    ACCUMULATOR = 3,
    OUTPUT = 4,
    ACCUMULATOR_8BIT = 5,
};
using SramAddr = Unsigned<MEM_OP_SRAM_ADDR_BIT_WIDTH>;
using DramAddr = Unsigned<MEM_OP_DRAM_ADDR_BIT_WIDTH>;
using MemorySize = Unsigned<MEM_OP_SIZE_BIT_WIDTH>;
using Stride = Unsigned<MEM_OP_STRIDE_BIT_WIDTH>;
using Pad = Unsigned<MEM_OP_PAD_BIT_WIDTH>;

using LoopIterIndex = Unsigned<LOOP_ITER_WIDTH>;
using MicroOpIndex = Unsigned<LOG_MICRO_OP_BUFFER_DEPTH>;
using InputIndex = Unsigned<LOG_INPUT_BUFFER_DEPTH>;
using WeightIndex = Unsigned<LOG_WEIGHT_BUFFER_DEPTH>;
using AccumulatorIndex = Unsigned<LOG_ACCUMULATOR_BUFFER_DEPTH>;
enum class AluOpcode : Unsigned<ALU_OPCODE_BIT_WIDTH>
{
    MIN = 0,
    MAX = 1,
    ADD = 2,
    SHR = 3,
    MUL = 4,
};
using Immediate = Signed<ALU_OP_IMMEDIATE_BIT_WIDTH>;
using ShrData = Signed<ALU_OP_SHR_BIT_WIDTH>;
using MulData = Signed<ALU_OP_MUL_BIT_WIDTH>;

#pragma pack(1)
struct Instruction
{
    InstructionData data;

    struct CommonInstruction
    {
        Opcode opcode : OPCODE_BIT_WIDTH;
        bool pop_prev_dependence : 1;
        bool pop_next_dependence : 1;
        bool push_prev_dependence : 1;
        bool push_next_dependence : 1;
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
        bool pop_prev_dependence : 1;
        bool pop_next_dependence : 1;
        bool push_prev_dependence : 1;
        bool push_next_dependence : 1;
        MemoryId memory_type : MEM_OP_ID_BIT_WIDTH;
        SramAddr sram_base : MEM_OP_SRAM_ADDR_BIT_WIDTH;
        DramAddr dram_base : MEM_OP_DRAM_ADDR_BIT_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 4 - MEM_OP_ID_BIT_WIDTH -
            MEM_OP_SRAM_ADDR_BIT_WIDTH - MEM_OP_DRAM_ADDR_BIT_WIDTH;
        MemorySize y_size : MEM_OP_SIZE_BIT_WIDTH;
        MemorySize x_size : MEM_OP_SIZE_BIT_WIDTH;
        Stride x_stride : MEM_OP_STRIDE_BIT_WIDTH;
        Pad y_pad_0 : MEM_OP_PAD_BIT_WIDTH;
        Pad y_pad_1 : MEM_OP_PAD_BIT_WIDTH;
        Pad x_pad_0 : MEM_OP_PAD_BIT_WIDTH;
        Pad x_pad_1 : MEM_OP_PAD_BIT_WIDTH;
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
        bool pop_prev_dependence : 1;
        bool pop_next_dependence : 1;
        bool push_prev_dependence : 1;
        bool push_next_dependence : 1;
        bool reset_reg : 1;
        MicroOpIndex micro_op_begin : LOG_MICRO_OP_BUFFER_DEPTH;
        MicroOpIndex micro_op_end : LOG_MICRO_OP_BUFFER_DEPTH + 1;
        LoopIterIndex iter_outer : LOOP_ITER_WIDTH;
        LoopIterIndex iter_inner : LOOP_ITER_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 6 - 2 * LOG_MICRO_OP_BUFFER_DEPTH -
            2 * LOOP_ITER_WIDTH;
        AccumulatorIndex accumulator_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        AccumulatorIndex accumulator_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        InputIndex input_factor_in : LOG_INPUT_BUFFER_DEPTH;
        InputIndex input_factor_out : LOG_INPUT_BUFFER_DEPTH;
        WeightIndex weight_factor_in : LOG_WEIGHT_BUFFER_DEPTH;
        WeightIndex weight_factor_out : LOG_WEIGHT_BUFFER_DEPTH;
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
        bool pop_prev_dependence : 1;
        bool pop_next_dependence : 1;
        bool push_prev_dependence : 1;
        bool push_next_dependence : 1;
        bool reset_reg : 1;
        MicroOpIndex micro_op_begin : LOG_MICRO_OP_BUFFER_DEPTH;
        MicroOpIndex micro_op_end : LOG_MICRO_OP_BUFFER_DEPTH + 1;
        LoopIterIndex iter_outer : LOOP_ITER_WIDTH;
        LoopIterIndex iter_inner : LOOP_ITER_WIDTH;
        uint64_t : 64 - OPCODE_BIT_WIDTH - 6 - 2 * LOG_MICRO_OP_BUFFER_DEPTH -
            2 * LOOP_ITER_WIDTH;
        AccumulatorIndex dst_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        AccumulatorIndex dst_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        InputIndex src_factor_out : LOG_ACCUMULATOR_BUFFER_DEPTH;
        InputIndex src_factor_in : LOG_ACCUMULATOR_BUFFER_DEPTH;
        AluOpcode alu_opcode : ALU_OPCODE_BIT_WIDTH;
        bool use_imm : 1;
        union
        {
            Immediate imm : ALU_OP_IMMEDIATE_BIT_WIDTH;
            ShrData shr : ALU_OP_SHR_BIT_WIDTH;
            MulData mul : ALU_OP_MUL_BIT_WIDTH;
        };
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

using MemoryInstruction = Instruction::MemoryInstruction;
using GemmInstruction = Instruction::GemmInstruction;
using AluInstruction = Instruction::AluInstruction;

using InputBuffer =
    std::array<std::array<Bus, INPUT_MATRIX_RATIO>, INPUT_BUFFER_DEPTH>;
using WeightBuffer =
    std::array<std::array<Bus, WEIGHT_MATRIX_RATIO>, WEIGHT_BUFFER_DEPTH>;
using OutputBuffer =
    std::array<std::array<Bus, OUTPUT_MATRIX_RATIO>, OUTPUT_BUFFER_DEPTH>;

} // namespace vta

#endif
