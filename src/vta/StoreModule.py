from m5.params import *
from m5.SimObject import SimObject


class StoreModule(SimObject):
    type = "StoreModule"
    cxx_header = "vta/store_module.hh"
    cxx_class = "gem5::StoreModule"

    store_queue = Param.InstructionQueue(NULL, "store instruction queue")

    cmp2st_queue = Param.DataQueue(
        NULL, "computer module to store module queue"
    )
    st2cmp_queue = Param.DataQueue(
        NULL, "store module to computer module queue"
    )

    output_buffer = Param.Buffer(NULL, "VTA outputbuffer")
