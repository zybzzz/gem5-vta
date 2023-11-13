from m5.params import *
from m5.SimObject import SimObject
from m5.objects.InstQueues import *


class ComputerModule(SimObject):
    type = "ComputerModule"
    abstract = False
    cxx_header = "vta/computer_module.hh"
    cxx_class = "gem5::ComputerModule"

    computer_queue = Param.BaseInstructionQueue(
        NULL, "computer instruction queue"
    )

    cmp2st_queue = Param.CMP2STQueue(
        NULL, "computer module to store module queue"
    )
    st2cmp_queue = Param.ST2CMPQueue(
        NULL, "store module to computer module queue"
    )
    cmp2ld_queue = Param.CMP2LDQueue(
        NULL, "computer module to load module queue"
    )
    ld2cmp_queue = Param.LD2CMPQueue(
        NULL, "load module to computer module queue"
    )

    input_buffer = Param.InputBuffer(NULL, "VTA inputbuffer")
    weight_buffer = Param.WeightBuffer(NULL, "VTA weightbuffer")
    output_buffer = Param.OutputBuffer(NULL, "VTA outputbuffer")

    # def __init__(self):
    #     super().__init__()
    #     pass
