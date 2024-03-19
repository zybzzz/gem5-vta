from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Buffer import *
from m5.objects.CommandQueue import *
from m5.objects.DependencyQueue import *


class LoadModule(SimObject):
    type = "LoadModule"
    cxx_header = "vta/load_module.hh"
    cxx_class = "gem5::LoadModule"

    load_command_queue = Param.CommandQueue("load command queue")

    load_to_compute_queue = Param.DependencyQueue(
        "load module to compute module queue"
    )
    compute_to_load_queue = Param.DependencyQueue(
        "compute module to load module queue"
    )

    input_buffer = Param.InputBuffer("VTA input buffer")
    weight_buffer = Param.WeightBuffer("VTA weight buffer")
