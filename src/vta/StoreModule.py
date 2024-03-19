from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Buffer import *
from m5.objects.CommandQueue import *
from m5.objects.DependencyQueue import *


class StoreModule(SimObject):
    type = "StoreModule"
    cxx_header = "vta/store_module.hh"
    cxx_class = "gem5::StoreModule"

    store_command_queue = Param.CommandQueue("store command queue")

    compute_to_store_queue = Param.DependencyQueue(
        "compute module to store module queue"
    )
    store_to_compute_queue = Param.DependencyQueue(
        "store module to compute module queue"
    )

    output_buffer = Param.OutputBuffer("VTA output buffer")
