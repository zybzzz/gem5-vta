from m5.params import *
from m5.SimObject import SimObject


class Buffer(SimObject):
    type = "Buffer"
    cxx_header = "vta/buffer.hh"
    cxx_class = "gem5::Buffer"
