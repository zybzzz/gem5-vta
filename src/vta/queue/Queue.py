from m5.SimObject import SimObject


class CommandQueue(SimObject):
    type = "CommandQueue"
    cxx_header = "vta/queue/command_queue.hh"
    cxx_class = "gem5::CommandQueue"


class DependencyQueue(SimObject):
    type = "DependencyQueue"
    cxx_header = "vta/queue/dependency_queue.hh"
    cxx_class = "gem5::DependencyQueue"
