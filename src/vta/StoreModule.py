from m5.params import *
from m5.SimObject import SimObject


class StoreModule(SimObject):
    type = "StoreModule"
    cxx_header = "vta/store_module.hh"
    cxx_class = "gem5::StoreModule"

    store_command_queue = Param.InstructionQueue(NULL, "store command queue")

    compute_to_store_queue = Param.DataQueue(
        NULL, "compute module to store module queue"
    )
    store_to_compute_queue = Param.DataQueue(
        NULL, "store module to compute module queue"
    )

    output_buffer = Param.Buffer(NULL, "VTA output buffer")
