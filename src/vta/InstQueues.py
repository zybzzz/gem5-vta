from m5.params import *
from m5.SimObject import SimObject


class BaseInstructionQueue(SimObject):
    type = "BaseInstructionQueue"
    abstract = True
    cxx_header = "vta/base_instruction_queue.hh"
    cxx_class = "gem5::BaseInstructionQueue"


class LoadQueue(BaseInstructionQueue):
    type = "LoadQueue"
    abstract = False
    cxx_header = "vta/inst_queues.hh"
    cxx_class = "gem5::LoadQueue"


class ComputerQueue(BaseInstructionQueue):
    type = "ComputerQueue"
    abstract = False
    cxx_header = "vta/inst_queues.hh"
    cxx_class = "gem5::ComputerQueue"


class StoreQueue(BaseInstructionQueue):
    type = "StoreQueue"
    abstract = False
    cxx_header = "vta/inst_queues.hh"
    cxx_class = "gem5::StoreQueue"
