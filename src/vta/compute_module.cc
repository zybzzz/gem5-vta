#include "vta/compute_module.hh"
#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "vta/vta.hh"


#include "vta/vta_const.hh"
#include <bitset>



//computmodule type define   same as  vta.h
// 计算无符号整数类型的位宽
constexpr int acc_idx_T_width =  LOG_ACCUMULATOR_BUFFER_DEPTH + 1;
constexpr int inp_idx_T_width =  LOG_INPUT_BUFFER_DEPTH + 1;
constexpr int wgt_idx_T_width =  LOG_WEIGHT_BUFFER_DEPTH + 1;
constexpr int micro_op_width  =  MICRO_OP_WIDTH;
constexpr int t = ACCUMULATOR_WIDTH;


// 使用 std::bitset 定义 acc_idx_T 类型
using acc_idx_T = std::bitset<acc_idx_T_width>;
using inp_idx_T = std::bitset<inp_idx_T_width>;
using wgt_idx_T = std::bitset<wgt_idx_T_width>;
using uop_T = std::bitset<micro_op_width>;
using wgt_T = std::bitset<WEIGHT_WIDTH>;
using bus_T = std::bitset<BUS_WIDTH>;
using inp_T = std::bitset<INPUT_WIDTH>;
using acc_T = std::biset<ACCUMULATOR_WIDTH>;
using out_T = std::bitset<OUTPUT_WIDTH>;


namespace gem5
{
ComputeModule::ComputeModule(const Params &params) :
    SimObject(params),
    computeCommandQueue(params.compute_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create ComputeModule!\n");
}


ComputeModule::gemm(const Params &params):
    SimObject(params),
    computeCommandQueue(params.compute_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer)
{
    InputBuffer inputbuffer;
    WeightBuffer weightbuffer;
    OutputBuffer outputbuffer;
    MicroopBuffer microopbuffer;
    AccumulatorBuffer accumulatorbuffer;
    //get instruction
    GemmInstruction gemmInst = computeCommandQueue->pop();
    Instruction inst = gemmInst.operator Instruction();
    //load to IR register
    IR = inst;
    Opcode opcode = IR.opcode;
    //Instuction decode
    uint64_t uop_bgn = IR.micro_op_begin;
    uint64_t uop_end = IR.micro_op_end;

    uint64_t end0 = IR.iter_outer;
    uint64_t end1 = IR.iter_inner;

    uint64_t x0 =  IR.accumulator_factor_in;
    uint64_t x1 =  IR.accumulator_factor_out;

    uint64_t y0 = IR.input_factor_in;
    uint64_t y1 = IR.input_factor_out;

    uint64_t z0 = IR.weight_factor_in;
    uint34_t z1 = IR.weight_factor_out;


    //offset
    acc_idx_T dst_offset_out = 0;
    inp_idx_T src_offset_out = 0; 
    wgt_idx_T wgt_offset_out = 0;


    if( opcode == 2) {
        //OuterLoop
        for (int i0 = 0; i0 < end0; i0++) {
          //offset
          acc_idx_T dst_offset_in = dst_offset_out;
          inp_idx_T src_offset_in = src_offset_out;
          wgt_idx_T wgt_offset_in = wgt_offset_out;
          
          //Inner Loop
          for(int i1 = 0; i1 < end1; i1++) {

            //Iterate over micro_op
            for (int uop_idx = uop_bgn; uop_idx < uop_end; uop_idx++) {
                //decode micro op
                BusType uop = microopbuffer[uop_idx];
                acc_idx_T dst_idx = uop.slice(MICRO_OP_GEM_0_0,MICRO_OP_GEM_0_1) + dst_offset_in;
                inp_idx_T src_idx = uop.slice(MICRO_OP_GEM_1_0, MICRO_OP_GEM_1_1) + src_offset_in;
                wgt_idx_T wgt_idx = uop.slice(MICRO_OP_GEM_2_0, MICRO_OP_GEM_2_1) + wgt_offset_in;

                //Read in weight tensor
                wgt_T w_tensor[BLOCK_OUTPUT][BLOCK_INPUT];
                read_tensor<bus_T, wgt_T, wgt_idx_T, BUS_WIDTH, WEIGHT_WIDTH, BLOCK_OUTPUT, BLOCK_INPUT>(wgt_idx, weightbuffer, w_tensor);
                // Read in input tensor
                inp_T i_tensor[BATCH][BLOCK_INPUT];
                read_tensor<bus_T, inp_T, inp_idx_T, BUS_WIDTH, INPUT_WIDTH, BATCH, BLOCK_INPUT>(src_idx, inputbuffer, i_tensor);
                // Read in accum tensor
                acc_T a_tensor[BATCH][BLOCK_OUTPUT];
                 read_tensor<bus_T, acc_T, acc_idx_T, BUS_WIDTH, ACCUMULATOR_WIDTH, BATCH, BLOCK_OUT>(dst_idx,accumulatorbuffer, a_tensor);
                //output tensor
                out_T o_tensor[BATCH][BLOCK_OUTPUT];



                //inner gemm loop
                for (int b = 0; b < BATCH; b++) {
                    for (int oc = 0; oc < BLOCK_OUTPUT; oc++) {
                        acc_T accum = a_tensor[b][oc];
                        sum_T tmp = 0;
                        for (int ic = 0; ic < BLOCK_INPUT; ic++) {
                            wgt_T w_elem = w_tensor[oc][ic];
                            inp_T i_elem = i_tensor[b][ic];
                            mul_T prod_dsp = i_elem * w_elem;
                            tmp += (sum_T) prod_dsp;
                        }
                        // Update summation
                        accum += (acc_T) tmp;
                        // Write back result acc_mem
                        a_tensor[b][oc] = IR.reset_reg ? (acc_T) 0 : accum;
                        // And output vector
                        o_tensor[b][oc] = (out_T) accum.range(VTA_OUT_WIDTH - 1, 0);
                    }
                }
             // Write the results back into accumulator
            write_tensor<bus_T, acc_T, acc_idx_T, BUS_WIDTH, ACCUMULATOR_WIDTH, BATCH, BLOCK_OUTPUT>(dst_idx, a_tensor, accumulatorbuffer);
            // Write the results back in the output buffer
            write_tensor<bus_T, out_T, acc_idx_T, BUS_WIDTH, OUTPUT_WIDTH, BATCH, BLOCK_OUTPUT>(dst_idx, o_tensor, outputbuffer);           
            }
            //Update offsets
           dst_offset_in += IR.accumulator_factor_in;
           src_offset_in += IR.input_factor_in;
           wgt_offset_in += IR.weight_factor_in;
          }

           dst_offset_out += IR.accumulator_factor_out;
           src_offset_out += IR.input_factor_out;
           wgt_offset_out += IR.weight_factor_out;
        }
    }
}



} // namespace gem5
