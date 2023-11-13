from m5.params import *
from m5.SimObject import SimObject


class LoadModule(SimObject):
    type = "LoadModule"
    cxx_header = "vta/load_module.hh"
    cxx_class = "gem5::LoadModule"

    load_command_queue = Param.InstructionQueue(NULL, "load command queue")

    cmp2ld_queue = Param.DataQueue(NULL, "compute module to load module queue")
    ld2cmp_queue = Param.DataQueue(NULL, "load module to compute module queue")

    input_buffer = Param.Buffer(NULL, "VTA input buffer")
    weight_buffer = Param.Buffer(NULL, "VTA weight buffer")
