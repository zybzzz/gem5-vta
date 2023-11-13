from m5.params import *
from m5.SimObject import SimObject


class InstructionQueue(SimObject):
    type = "InstructionQueue"
    cxx_header = "vta/instruction_queue.hh"
    cxx_class = "gem5::InstructionQueue"
