#include "vta/base_vta.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
BaseVTA::BaseVTA(const Params &params) :
    SimObject(params),
    begin_event([this] { processBeginEvent(); }, name() + ".beginEvent"),
    hardware_version(params.HW_VER),
    input_data_width(1 << params.LOG_INP_WIDTH),
    weight_data_width(1 << params.LOG_WGT_WIDTH),
    accumulator_data_width(1 << params.LOG_ACC_WIDTH),
    batch_size(1 << params.LOG_BATCH),
    block_size(1 << params.LOG_BLOCK),
    uop_buffer_size(1 << params.LOG_UOP_BUFF_SIZE),
    input_buffer_size(1 << params.LOG_INP_BUFF_SIZE),
    weight_buffer_size(1 << params.LOG_WGT_BUFF_SIZE),
    accumulator_buffer_size(1 << params.LOG_ACC_BUFF_SIZE)
{
    DPRINTF(BaseVTAFlag, "===========================================\n");

    DPRINTF(BaseVTAFlag, "initializing gem5-vta ... user configuration "
                         "parameters are as follows: \n");
    DPRINTF(BaseVTAFlag, "hardware_version: %10s\n", hardware_version.c_str());
    DPRINTF(BaseVTAFlag, "input_data_width: %10d\n", input_data_width);
    DPRINTF(BaseVTAFlag, "weight_data_width: %10d\n", weight_data_width);
    DPRINTF(
        BaseVTAFlag, "accumulator_data_width: %10d\n", accumulator_data_width);
    DPRINTF(BaseVTAFlag, "batch_size: %10d\n", batch_size);
    DPRINTF(BaseVTAFlag, "block_size: %10d\n", block_size);
    DPRINTF(BaseVTAFlag, "uop_buffer_size: %10d\n", uop_buffer_size);
    DPRINTF(BaseVTAFlag, "input_buffer_size: %10d\n", input_buffer_size);
    DPRINTF(BaseVTAFlag, "weight_buffer_size: %10d\n", weight_buffer_size);
    DPRINTF(BaseVTAFlag, "accumulator_buffer_size: %10d\n",
        accumulator_buffer_size);

    DPRINTF(BaseVTAFlag, "===========================================\n");
}

void
BaseVTA::startup()
{
    // DPRINTF(BaseVTAFlag, "%s: start up in BaseVTA.\n", __func__);
    // schedule(begin_event, 100);
}

void
BaseVTA::processBeginEvent()
{
    // DPRINTF(BaseVTAFlag, "%s: process event up in BaseVTA.\n", __func__);
}
} // namespace gem5
