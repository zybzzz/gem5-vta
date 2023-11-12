from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstQueues import *

class InstructionFetchModule(SimObject):
    type = "InstructionFetchModule"
    abstract = False
    cxx_header = "vta/instruction_fetch_module.hh"
    cxx_class = "gem5::InstructionFetchModule"

    # FIXME this will cause error, but I don't know why
    # load_queue = Param.LoadQueue("load instruction queue")
    # computer_queue = Param.ComputerQueue("computer instruction queue")
    # store_queue = Param.StoreQueue("store instruction queue")

    # The type must be the same as declared in the c++ file
    load_queue = Param.BaseInstructionQueue(NULL, "load instruction queue")
    computer_queue = Param.BaseInstructionQueue(NULL, "computer instruction queue")
    store_queue = Param.BaseInstructionQueue(NULL, "store instruction queue")

    #TODO connect to DRAM

    # def __init__(self, **kwargs):
    #     super().__init__(**kwargs)
    #     pass