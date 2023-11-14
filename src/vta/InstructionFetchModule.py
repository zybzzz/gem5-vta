from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstructionQueue import *


class InstructionFetchModule(SimObject):
    type = "InstructionFetchModule"
    cxx_header = "vta/instruction_fetch_module.hh"
    cxx_class = "gem5::InstructionFetchModule"

    # FIXME this will cause error, but I don't know why
    # load_command_queue = Param.InstructionQueue("load command queue")
    # compute_command_queue = Param.InstructionQueue("compute command queue")
    # store_command_queue = Param.InstructionQueue("store command queue")

    # The type must be the same as declared in the c++ file
    load_command_queue = Param.InstructionQueue(NULL, "load command queue")
    compute_command_queue = Param.InstructionQueue(
        NULL, "compute command queue"
    )
    store_command_queue = Param.InstructionQueue(NULL, "store command queue")

    # TODO connect to DRAM

    # def __init__(self, **kwargs):
    #     super().__init__(**kwargs)
    #     pass
