from m5.SimObject import SimObject


class DependencyQueue(SimObject):
    type = "DependencyQueue"
    cxx_header = "vta/dependency_queue.hh"
    cxx_class = "gem5::DependencyQueue"
