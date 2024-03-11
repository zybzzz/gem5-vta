from m5.SimObject import SimObject


class CommandQueue(SimObject):
    type = "CommandQueue"
    cxx_header = "vta/command_queue.hh"
    cxx_class = "gem5::CommandQueue"
