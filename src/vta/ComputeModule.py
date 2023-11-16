from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstructionQueue import *


class ComputeModule(SimObject):
    type = "ComputeModule"
    cxx_header = "vta/compute_module.hh"
    cxx_class = "gem5::ComputeModule"

    compute_command_queue = Param.InstructionQueue(
        NULL, "compute command queue"
    )

    compute_to_store_queue = Param.DataQueue(
        NULL, "compute module to store module queue"
    )
    store_to_compute_queue = Param.DataQueue(
        NULL, "store module to compute module queue"
    )
    compute_to_load_queue = Param.DataQueue(
        NULL, "compute module to load module queue"
    )
    load_to_compute_queue = Param.DataQueue(
        NULL, "load module to compute module queue"
    )

    input_buffer = Param.Buffer(NULL, "VTA input buffer")
    weight_buffer = Param.Buffer(NULL, "VTA weight buffer")
    output_buffer = Param.Buffer(NULL, "VTA output buffer")

    # def __init__(self):
    #     super().__init__()
    #     pass
