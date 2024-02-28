#ifndef VTA_CONST_HH
#define VTA_CONST_HH

#include <cstddef>
#include <cstdint>

#include "vta/vta_config.hh"
#include "vta/vta_hw_config.hh"

namespace vta
{

// Memory buf width
constexpr size_t BUS_WIDTH{1 << LOG_BUS_WIDTH};

// Instruction width and size
constexpr size_t LOG_INSTRUCTION_WIDTH{7};
constexpr size_t INSTRUCTION_WIDTH{1 << LOG_INSTRUCTION_WIDTH};
constexpr size_t INSTRUCTION_SIZE{INSTRUCTION_WIDTH / 8};

// Micro op width and size
constexpr size_t LOG_MICRO_OP_WIDTH{5};
constexpr size_t MICRO_OP_WIDTH{1 << LOG_MICRO_OP_WIDTH};
constexpr size_t MICRO_OP_SIZE{MICRO_OP_WIDTH / 8};

constexpr size_t INPUT_WIDTH{1 << LOG_INPUT_WIDTH};
constexpr size_t WEIGHT_WIDTH{1 << LOG_WEIGHT_WIDTH};
constexpr size_t ACCUMULATOR_WIDTH{1 << LOG_ACCUMULATOR_WIDTH};
constexpr size_t LOG_OUTPUT_WIDTH{LOG_INPUT_WIDTH};
constexpr size_t OUTPUT_WIDTH{1 << LOG_OUTPUT_WIDTH};

// Batch
constexpr size_t BATCH{1 << LOG_BATCH};

// Block
constexpr size_t LOG_BLOCK_IN{LOG_BLOCK};
constexpr size_t LOG_BLOCK_OUT{LOG_BLOCK};
constexpr size_t BLOCK_INPUT{1 << LOG_BLOCK_IN};
constexpr size_t BLOCK_OUTPUT{1 << LOG_BLOCK_OUT};

// Matrix width and size
constexpr size_t INPUT_MATRIX_WIDTH{INPUT_WIDTH * BATCH * BLOCK_INPUT};
constexpr size_t INPUT_MATRIX_SIZE{INPUT_MATRIX_WIDTH / 8};
constexpr size_t WEIGHT_MATRIX_WIDTH{
    WEIGHT_WIDTH * BLOCK_OUTPUT * BLOCK_INPUT};
constexpr size_t WEIGHT_MATRIX_SIZE{WEIGHT_MATRIX_WIDTH / 8};
constexpr size_t ACCUMULATOR_MATRIX_WIDTH{
    ACCUMULATOR_WIDTH * BATCH * BLOCK_OUTPUT};
constexpr size_t ACCUMULATOR_MATRIX_SIZE{ACCUMULATOR_MATRIX_WIDTH / 8};
constexpr size_t OUTPUT_MATRIX_WIDTH{OUTPUT_WIDTH * BATCH * BLOCK_OUTPUT};
constexpr size_t OUTPUT_MATRIX_SIZE{OUTPUT_MATRIX_WIDTH / 8};

// Ratio between matrix width and bus width
constexpr size_t INPUT_MATRIX_RATIO{INPUT_MATRIX_WIDTH / BUS_WIDTH};
constexpr size_t WEIGHT_MATRIX_RATIO{WEIGHT_MATRIX_WIDTH / BUS_WIDTH};
constexpr size_t ACCUMULATOR_MATRIX_RATIO{
    ACCUMULATOR_MATRIX_WIDTH / BUS_WIDTH};
constexpr size_t OUTPUT_MATRIX_RATIO{OUTPUT_MATRIX_WIDTH / BUS_WIDTH};

// Buffer size
constexpr size_t MICRO_OP_BUFFER_SIZE{1 << LOG_MICRO_OP_BUFFER_SIZE};
constexpr size_t INPUT_BUFFER_SIZE{1 << LOG_INPUT_BUFFER_SIZE};
constexpr size_t WEIGHT_BUFFER_SIZE{1 << LOG_WEIGHT_BUFFER_SIZE};
constexpr size_t ACCUMULATOR_BUFFER_SIZE{1 << LOG_ACCUMULATOR_BUFFER_SIZE};

// Buffer depth
constexpr size_t LOG_MICRO_OP_BUFFER_DEPTH{
    LOG_MICRO_OP_BUFFER_SIZE - LOG_MICRO_OP_WIDTH + 3};
constexpr size_t MICRO_OP_BUFFER_DEPTH{1 << LOG_MICRO_OP_BUFFER_DEPTH};
constexpr size_t LOG_INPUT_BUFFER_DEPTH{
    LOG_INPUT_BUFFER_SIZE - LOG_BATCH - LOG_BLOCK_IN - LOG_INPUT_WIDTH + 3};
constexpr size_t INPUT_BUFFER_DEPTH{1 << LOG_INPUT_BUFFER_DEPTH};
constexpr size_t LOG_WEIGHT_BUFFER_DEPTH{LOG_WEIGHT_BUFFER_SIZE -
                                         LOG_BLOCK_OUT - LOG_BLOCK_IN -
                                         LOG_WEIGHT_WIDTH + 3};
constexpr size_t WEIGHT_BUFFER_DEPTH{1 << LOG_WEIGHT_BUFFER_DEPTH};
constexpr size_t LOG_ACCUMULATOR_BUFFER_DEPTH{LOG_ACCUMULATOR_BUFFER_SIZE -
                                              LOG_BATCH - LOG_BLOCK_OUT -
                                              LOG_ACCUMULATOR_WIDTH + 3};
constexpr size_t ACCUMULATOR_BUFFER_DEPTH{1 << LOG_ACCUMULATOR_BUFFER_DEPTH};
constexpr size_t LOG_OUTPUT_BUFFER_DEPTH{LOG_INPUT_BUFFER_DEPTH};
constexpr size_t OUTPUT_BUFFER_DEPTH{1 << LOG_OUTPUT_BUFFER_DEPTH};


//computmodule type define   same as  vta.h
constexpr int acc_idx_T_width =  LOG_ACCUMULATOR_BUFFER_DEPTH + 1;
constexpr int inp_idx_T_width =  LOG_INPUT_BUFFER_DEPTH + 1;
constexpr int wgt_idx_T_width =  LOG_WEIGHT_BUFFER_DEPTH + 1;
constexpr int micro_op_width  =  MICRO_OP_WIDTH;
constexpr int t = ACCUMULATOR_WIDTH;



// Opcode
constexpr size_t OPCODE_BIT_WIDTH{3};

enum class Opcode : uint8_t
{
    LOAD = 0,
    STORE = 1,
    GEMM = 2,
    FINISH = 3,
    ALU = 4,
};

// ALU opcode
constexpr size_t ALU_OPCODE_BIT_WIDTH{3};

enum class AluOpcode : uint8_t
{
    MIN = 0,
    MAX = 1,
    ADD = 2,
    SHR = 3,
    MUL = 4,
};

// Load, Store
constexpr size_t MEM_OP_ID_BIT_WIDTH{3};
constexpr size_t MEM_OP_SRAM_ADDR_BIT_WIDTH{16};
constexpr size_t MEM_OP_DRAM_ADDR_BIT_WIDTH{32};
constexpr size_t MEM_OP_SIZE_BIT_WIDTH{16};
constexpr size_t MEM_OP_STRIDE_BIT_WIDTH{16};
constexpr size_t MEM_OP_PAD_BIT_WIDTH{4};

// GEMM/ALU
constexpr size_t LOOP_ITER_WIDTH{14};
//add code same as vta
/*! GEMM Micro-op start position of the acc_idx field */
constexpr size_t MICRO_OP_GEM_0_0{0};
/*! GEMM Micro-op end position of the acc_idx field */
constexpr size_t MICRO_OP_GEM_0_1{MICRO_OP_GEM_0_0 + LOG_ACCUMULATOR_BUFFER_DEPTH - 1};
/*! GEMM Micro-op start position of the inp_idx field */
constexpr size_t MICRO_OP_GEM_1_0{MICRO_OP_GEM_0_1 + 1};
/*! GEMM Micro-op end position of the inp_idx field */
constexpr size_t MICRO_OP_GEM_1_1{MICRO_OP_GEM_1_0 + LOG_INPUT_BUFFER_DEPTH - 1};
/*! GEMM Micro-op start position of the wgt_idx field */
constexpr size_t MICRO_OP_GEM_2_0{MICRO_OP_GEM_1_1 + 1};
/*! GEMM Micro-op end position of the wgt_idx field */
constexpr size_t MICRO_OP_GEM_2_1{MICRO_OP_GEM_2_0 + LOG_WEIGHT_BUFFER_DEPTH - 1};

//ALU
/*! GEMM Micro-op start position of the acc_idx field */
constexpr size_t MICRO_OP_ALU_0_0{0};
/*! GEMM Micro-op end position of the acc_idx field */
constexpr size_t MICRO_OP_ALU_0_1{MICRO_OP_ALU_0_0 + LOG_ACCUMULATOR_BUFFER_DEPTH - 1};
/*! GEMM Micro-op start position of the inp_idx field */
constexpr size_t MICRO_OP_ALU_0_0{MICRO_OP_ALU_0_1 + 1};
/*! GEMM Micro-op end position of the inp_idx field */
constexpr size_t MICRO_OP_ALU_0_0{MICRO_OP_ALU_0_1 + LOG_INPUT_BUFFER_DEPTH - 1};

// ALU
constexpr size_t ALU_OP_IMMEDIATE_BIT_WIDTH{16};
constexpr size_t ALU_OP_SHR_WIDTH{LOG_ACCUMULATOR_WIDTH};
constexpr size_t ALU_OP_MUL_WIDTH{8};

enum class MemoryId : uint8_t
{
    MICRO_OP = 0,
    WEIGHT = 1,
    INPUT = 2,
    ACCUMULATOR = 3,
    OUTPUT = 4,
    ACCUMULATOR_8BIT = 5,
};

} // namespace vta

#endif
