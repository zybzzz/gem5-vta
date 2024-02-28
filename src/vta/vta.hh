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
};

using BusType = std::array<uint8_t, BUS_WIDTH / 8>;

using CommandQueue = Stream<Instruction, STREAM_IN_DEPTH>;
using DependencyQueue = Stream<Instruction, STREAM_IN_DEPTH>;




//use std::bitset to define some type
using acc_idx_T = std::bitset<acc_idx_T_width>;
using inp_idx_T = std::bitset<inp_idx_T_width>;
using wgt_idx_T = std::bitset<wgt_idx_T_width>;
using uop_T = std::bitset<micro_op_width>;
using wgt_T = std::bitset<WEIGHT_WIDTH>;
using bus_T = std::bitset<BUS_WIDTH>;
using inp_T = std::bitset<INPUT_WIDTH>;
using acc_T = std::biset<ACCUMULATOR_WIDTH>;
using out_T = std::bitset<OUTPUT_WIDTH>;
using insn_T = std::bitset<INSTRUCTION_WIDTH>;



/*
array INPUT_MATRIX_RATIO first dim , INPUT_BUFFER_DEPTH second dim
*/
using InputBuffer =
    std::array<std::array<BusType, INPUT_MATRIX_RATIO>, INPUT_BUFFER_DEPTH>;
using WeightBuffer =
    std::array<std::array<BusType, WEIGHT_MATRIX_RATIO>, WEIGHT_BUFFER_DEPTH>;
using OutputBuffer =
    std::array<std::array<BusType, OUTPUT_MATRIX_RATIO>, OUTPUT_BUFFER_DEPTH>;

using AccumulatorBuffer = 
    std::array<std::array<BusType, ACCUMULATOR_MATRIX_RATIO>, ACCUMULATOR_BUFFER_DEPTH>;
//add micro_opBuffer
using MicroopBuffer = 
      std::array<std::array<BusType,MICRO_OP_BUFFER_DEPTH>>;


//read_tensor
template <typename WIDE_T, typename NARROW_T, typename IDX_T, int WIDE_W, int NARROW_W, int Y_DIM, int X_DIM>
void read_tensor(
    IDX_T idx,
    const std::array<std::array<WIDE_T, NARROW_W * Y_DIM * X_DIM / WIDE_W>, Y_DIM>& src,
    std::array<std::array<NARROW_T, X_DIM>, Y_DIM>& dst) {

    // Read in weight tensor
    for (int p = 0; p < NARROW_W * Y_DIM * X_DIM / WIDE_W; p++) {
        WIDE_T packet = src[idx][p];
        for (int w = 0; w < (WIDE_W / NARROW_W); w++) {
            int x = (p * (WIDE_W / NARROW_W) + w) / X_DIM;
            int y = (p * (WIDE_W / NARROW_W) + w) % X_DIM;
            dst[x][y] = static_cast<NARROW_T>(packet >> (w * NARROW_W)) & ((1 << NARROW_W) - 1);
        }
    }
}

//write_tensor
template <typename WIDE_T, typename NARROW_T, typename IDX_T, int WIDE_W, int NARROW_W, int Y_DIM, int X_DIM>
void write_tensor(
  IDX_T idx,
  NARROW_T src[Y_DIM][X_DIM],
  WIDE_T dst[][NARROW_W * Y_DIM * X_DIM / WIDE_W]) {
#pragma HLS INLINE

  for (int p = 0; p < NARROW_W * Y_DIM * X_DIM / WIDE_W; p++) {
    WIDE_T packet = 0;
    for (int w = 0; w < (WIDE_W / NARROW_W); w++) {
      int x = (p * (WIDE_W / NARROW_W) + w) / X_DIM;
      int y = (p * (WIDE_W / NARROW_W) + w) % X_DIM;
      packet.range((w + 1) * NARROW_W - 1, w * NARROW_W) = src[x][y];
    }
    dst[idx][p] = packet;
  }
}

} // namespace vta

#endif
