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

    cmp2st_queue = Param.DataQueue(
        NULL, "compute module to store module queue"
    )
    st2cmp_queue = Param.DataQueue(
        NULL, "store module to compute module queue"
    )
    cmp2ld_queue = Param.DataQueue(NULL, "compute module to load module queue")
    ld2cmp_queue = Param.DataQueue(NULL, "load module to compute module queue")

    input_buffer = Param.Buffer(NULL, "VTA inputbuffer")
    weight_buffer = Param.Buffer(NULL, "VTA weightbuffer")
    output_buffer = Param.Buffer(NULL, "VTA outputbuffer")

    # def __init__(self):
    #     super().__init__()
    #     pass
