from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Buffer import *
from m5.objects.ComputeModule import *
from m5.objects.DataQueue import *
from m5.objects.InstructionQueue import *
from m5.objects.InstructionFetchModule import *
from m5.objects.LoadModule import *
from m5.objects.StoreModule import *


class BaseVTA(SimObject):
    type = "BaseVTA"
    cxx_header = "vta/base_vta.hh"
    cxx_class = "gem5::BaseVTA"

    # VTA configs
    # reference at https://tvm.apache.org/docs/topic/vta/dev/config.html#parameters-overview

    ################################################################################
    ########################## the components of VTA ###############################

    ## buffers
    input_buffer = Param.Buffer(Buffer(), "VTA inputbuffer")
    weight_buffer = Param.Buffer(Buffer(), "VTA weightbuffer")
    output_buffer = Param.Buffer(Buffer(), "VTA outputbuffer")

    ## data queues
    cmp2st_queue = Param.DataQueue(
        DataQueue(), "compute module to store module queue"
    )
    st2cmp_queue = Param.DataQueue(
        DataQueue(), "store module to compute module queue"
    )
    cmp2ld_queue = Param.DataQueue(
        DataQueue(), "compute module to load module queue"
    )
    ld2cmp_queue = Param.DataQueue(
        DataQueue(), "load module to compute module queue"
    )

    ## command queues
    load_queue = Param.InstructionQueue(
        InstructionQueue(), "load command queue"
    )
    compute_command_queue = Param.InstructionQueue(
        InstructionQueue(), "compute command queue"
    )
    store_queue = Param.InstructionQueue(
        InstructionQueue(), "store command queue"
    )

    ## regular module
    instruction_fetch_module = Param.InstructionFetchModule(
        InstructionFetchModule(), "instruction fetch module"
    )
    compute_module = Param.ComputeModule(ComputeModule(), "compute module")
    load_module = Param.LoadModule(LoadModule(), "load module")
    store_module = Param.StoreModule(StoreModule(), "store module")

    ################################################################################
    ################################################################################

    ################################################################################
    ########################## pass params to components ###########################
    # instruction fetch module
    instruction_fetch_module.load_queue = load_queue
    instruction_fetch_module.compute_command_queue = compute_command_queue
    instruction_fetch_module.store_queue = store_queue

    # compute module
    compute_module.compute_command_queue = compute_command_queue
    compute_module.ld2cmp_queue = ld2cmp_queue
    compute_module.cmp2ld_queue = cmp2ld_queue
    compute_module.st2cmp_queue = st2cmp_queue
    compute_module.cmp2st_queue = cmp2st_queue
    compute_module.input_buffer = input_buffer
    compute_module.weight_buffer = weight_buffer
    compute_module.output_buffer = output_buffer

    # load module
    load_module.load_queue = load_queue
    load_module.cmp2ld_queue = cmp2ld_queue
    load_module.ld2cmp_queue = ld2cmp_queue
    load_module.input_buffer = input_buffer
    load_module.weight_buffer = weight_buffer

    # store module
    store_module.store_queue = store_queue
    store_module.cmp2st_queue = cmp2st_queue
    store_module.st2cmp_queue = st2cmp_queue
    store_module.output_buffer = output_buffer

    ################################################################################
    ################################################################################

    # def __init__(self, **kwargs):
    #     super().__init__(**kwargs)
    #     pass
