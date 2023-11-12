from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Buffers import *
from m5.objects.ComputerModule import *
from m5.objects.DataQueues import *
from m5.objects.InstQueues import *
from m5.objects.InstructionFetchModule import *
from m5.objects.LoadModule import *
from m5.objects.StoreModule import *


class BaseVTA(SimObject):
    type = "BaseVTA"
    abstract = False
    cxx_header = "vta/base_vta.hh"
    cxx_class = "gem5::BaseVTA"

    # VTA configs
    # reference at https://tvm.apache.org/docs/topic/vta/dev/config.html#parameters-overview
    HW_VER = Param.String("0.0.1", "VTA hardware version number.")
    LOG_INP_WIDTH = Param.Int(0, "Input data type signed integer width.")
    LOG_WGT_WIDTH = Param.Int(0, "Weight data type signed integer width.")
    LOG_ACC_WIDTH = Param.Int(0, "Accumulator data type signed integer width.")
    LOG_BATCH = Param.Int(0, "VTA matrix multiply intrinsic input/output dimension 0.")
    LOG_BLOCK = Param.Int(0, "VTA matrix multiply inner dimensions.")
    LOG_UOP_BUFF_SIZE = Param.Int(0, "Micro-op on-chip buffer in Bytes.")
    LOG_INP_BUFF_SIZE = Param.Int(0, "Input on-chip buffer in Bytes.")
    LOG_WGT_BUFF_SIZE = Param.Int(0, "Weight on-chip buffer in Bytes.")
    LOG_ACC_BUFF_SIZE = Param.Int(0, "Accumulator on-chip buffer in Bytes.")

    ################################################################################
    ########################## the components of VTA ###############################

    ## buffers
    input_buffer = Param.InputBuffer(InputBuffer(), "VTA inputbuffer")
    weight_buffer = Param.WeightBuffer(WeightBuffer(), "VTA weightbuffer")
    output_buffer = Param.OutputBuffer(OutputBuffer(), "VTA outputbuffer")

    ## data queues
    cmp2st_queue = Param.CMP2STQueue(CMP2STQueue(), "computer module to store module queue")
    st2cmp_queue = Param.ST2CMPQueue(ST2CMPQueue(), "store module to computer module queue")
    cmp2ld_queue = Param.CMP2LDQueue(CMP2LDQueue(), "computer module to load module queue")
    ld2cmp_queue = Param.LD2CMPQueue(LD2CMPQueue(), "load module to computer module queue")

    ## instruction queues
    load_queue = Param.LoadQueue(LoadQueue(), "load instruction queue")
    computer_queue = Param.ComputerQueue(ComputerQueue(), "computer instruction queue")
    store_queue = Param.StoreQueue(StoreQueue(), "store instruction queue")

    ## regular module
    instruction_fetch_module = Param.InstructionFetchModule(InstructionFetchModule(), "instruction fetch module")
    computer_module = Param.ComputerModule(ComputerModule(), "computer module")
    load_module = Param.LoadModule(LoadModule(), "load module")
    store_module = Param.StoreModule(StoreModule(), "store module")

    ################################################################################
    ################################################################################

    ################################################################################
    ########################## pass params to components ###########################
    # instruction fetch module
    instruction_fetch_module.load_queue = load_queue
    instruction_fetch_module.computer_queue = computer_queue
    instruction_fetch_module.store_queue = store_queue

    # computer module
    computer_module.computer_queue = computer_queue
    computer_module.ld2cmp_queue = ld2cmp_queue
    computer_module.cmp2ld_queue = cmp2ld_queue
    computer_module.st2cmp_queue = st2cmp_queue
    computer_module.cmp2st_queue = cmp2st_queue
    computer_module.input_buffer = input_buffer
    computer_module.weight_buffer = weight_buffer
    computer_module.output_buffer = output_buffer


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

