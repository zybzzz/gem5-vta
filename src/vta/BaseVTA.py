from m5.params import *
from m5.proxy import *
from m5.SimObject import SimObject
from m5.objects.Buffer import *
from m5.objects.CommandQueue import *
from m5.objects.ComputeModule import *
from m5.objects.InstructionFetchModule import *
from m5.objects.LoadModule import *
from m5.objects.StoreModule import *


class BaseVTA(SimObject):
    type = "BaseVTA"
    cxx_header = "vta/base_vta.hh"
    cxx_class = "gem5::BaseVTA"

    instruction_port = RequestPort("instruction port")
    micro_op_port = RequestPort("micro_op port")
    data_port = RequestPort("data port")

    system = Param.System(Parent.any, "system object")

    load_command_queue = CommandQueue()
    compute_command_queue = CommandQueue()
    store_command_queue = CommandQueue()

    instruction_fetch_module = InstructionFetchModule()
    instruction_fetch_module.load_command_queue = load_command_queue
    instruction_fetch_module.compute_command_queue = compute_command_queue
    instruction_fetch_module.store_command_queue = store_command_queue

    instruction_fetch_module = Param.InstructionFetchModule(
        instruction_fetch_module,
        "instruction fetch module",
    )

    # VTA configs
    # reference at https://tvm.apache.org/docs/topic/vta/dev/config.html#parameters-overview

    ################################################################################
    ########################## the components of VTA ###############################

    ## buffers
    input_buffer = Param.Buffer(Buffer(), "VTA input buffer")
    weight_buffer = Param.Buffer(Buffer(), "VTA weight buffer")
    output_buffer = Param.Buffer(Buffer(), "VTA output buffer")

    ## regular module
    compute_module = Param.ComputeModule(ComputeModule(), "compute module")
    load_module = Param.LoadModule(LoadModule(), "load module")
    store_module = Param.StoreModule(StoreModule(), "store module")

    # compute module
    compute_module.compute_command_queue = compute_command_queue
    compute_module.load_to_compute_queue = load_to_compute_queue
    compute_module.compute_to_load_queue = compute_to_load_queue
    compute_module.store_to_compute_queue = store_to_compute_queue
    compute_module.compute_to_store_queue = compute_to_store_queue
    compute_module.input_buffer = input_buffer
    compute_module.weight_buffer = weight_buffer
    compute_module.output_buffer = output_buffer

    # load module
    load_module.load_queue = load_queue
    load_module.compute_to_load_queue = compute_to_load_queue
    load_module.load_to_compute_queue = load_to_compute_queue
    load_module.input_buffer = input_buffer
    load_module.weight_buffer = weight_buffer

    # store module
    store_module.store_queue = store_queue
    store_module.compute_to_store_queue = compute_to_store_queue
    store_module.store_to_compute_queue = store_to_compute_queue
    store_module.output_buffer = output_buffer
