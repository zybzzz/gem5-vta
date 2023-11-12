from m5.params import *
from m5.SimObject import SimObject

class LoadModule(SimObject):
    type = "LoadModule"
    abstract = False
    cxx_header = "vta/load_module.hh"
    cxx_class = "gem5::LoadModule"

    load_queue = Param.BaseInstructionQueue(NULL, "load instruction queue")

    cmp2ld_queue = Param.CMP2LDQueue(NULL, "computer module to load module queue")
    ld2cmp_queue = Param.LD2CMPQueue(NULL, "load module to computer module queue")

    input_buffer = Param.InputBuffer(NULL, "VTA inputbuffer")
    weight_buffer = Param.WeightBuffer(NULL, "VTA weightbuffer")