from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Queue import *


class InstructionFetchModule(SimObject):
    type = "InstructionFetchModule"
    cxx_header = "vta/instruction_fetch_module.hh"
    cxx_class = "gem5::InstructionFetchModule"

    load_command_queue = Param.CommandQueue("load command queue")
    compute_command_queue = Param.CommandQueue("compute command queue")
    store_command_queue = Param.CommandQueue("store command queue")
