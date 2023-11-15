from m5.params import *
from m5.objects.ClockedObject import ClockedObject


class InstructionQueue(ClockedObject):
    type = "InstructionQueue"
    cxx_header = "vta/instruction_queue.hh"
    cxx_class = "gem5::InstructionQueue"

    queue_size = Param.Int(32, "length of the queue")
    latency = Param.Latency("1ns", "latency of the queue")
