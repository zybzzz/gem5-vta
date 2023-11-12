from m5.params import *
from m5.SimObject import SimObject

class StoreModule(SimObject):
    type = "StoreModule"
    abstract = False
    cxx_header = "vta/store_module.hh"
    cxx_class = "gem5::StoreModule"

    store_queue = Param.BaseInstructionQueue(NULL, "store instruction queue")

    cmp2st_queue = Param.CMP2STQueue(NULL, "computer module to store module queue")
    st2cmp_queue = Param.ST2CMPQueue(NULL, "store module to computer module queue")

    output_buffer = Param.OutputBuffer(NULL, "VTA outputbuffer")