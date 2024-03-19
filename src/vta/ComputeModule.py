from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Buffer import *
from m5.objects.CommandQueue import *
from m5.objects.DependencyQueue import *


class ComputeModule(SimObject):
    type = "ComputeModule"
    cxx_header = "vta/compute_module.hh"
    cxx_class = "gem5::ComputeModule"

    compute_command_queue = Param.CommandQueue("compute command queue")

    load_to_compute_queue = Param.DependencyQueue(
        "load module to compute module queue"
    )
    compute_to_load_queue = Param.DependencyQueue(
        "compute module to load module queue"
    )
    compute_to_store_queue = Param.DependencyQueue(
        "compute module to store module queue"
    )
    store_to_compute_queue = Param.DependencyQueue(
        "store module to compute module queue"
    )

    input_buffer = Param.InputBuffer("VTA input buffer")
    weight_buffer = Param.WeightBuffer("VTA weight buffer")
    output_buffer = Param.OutputBuffer("VTA output buffer")
