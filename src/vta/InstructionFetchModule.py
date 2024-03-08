from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstructionQueue import *


class InstructionFetchModule(SimObject):
    type = "InstructionFetchModule"
    cxx_header = "vta/instruction_fetch_module.hh"
    cxx_class = "gem5::InstructionFetchModule"

    instruction_port = RequestPort("instruction port")
