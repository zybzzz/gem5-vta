from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstructionQueue import *


class ComputerModule(SimObject):
    type = "ComputerModule"
    cxx_header = "vta/computer_module.hh"
    cxx_class = "gem5::ComputerModule"

    computer_queue = Param.InstructionQueue(NULL, "computer instruction queue")

    cmp2st_queue = Param.DataQueue(
        NULL, "computer module to store module queue"
    )
    st2cmp_queue = Param.DataQueue(
        NULL, "store module to computer module queue"
    )
    cmp2ld_queue = Param.DataQueue(
        NULL, "computer module to load module queue"
    )
    ld2cmp_queue = Param.DataQueue(
        NULL, "load module to computer module queue"
    )

    input_buffer = Param.Buffer(NULL, "VTA inputbuffer")
    weight_buffer = Param.Buffer(NULL, "VTA weightbuffer")
    output_buffer = Param.Buffer(NULL, "VTA outputbuffer")

    # def __init__(self):
    #     super().__init__()
    #     pass
