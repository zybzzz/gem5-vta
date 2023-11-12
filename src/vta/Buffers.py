from m5.params import *
from m5.SimObject import SimObject

class BaseBuffer(SimObject):
    type = "BaseBuffer"
    abstract = True
    cxx_header = "vta/base_buffer.hh"
    cxx_class = "gem5::BaseBuffer"

class InputBuffer(BaseBuffer):
    type = "InputBuffer"
    abstract = False
    cxx_header = "vta/buffers.hh"
    cxx_class = "gem5::InputBuffer"

class WeightBuffer(BaseBuffer):
    type = "WeightBuffer"
    abstract = False
    cxx_header = "vta/buffers.hh"
    cxx_class = "gem5::WeightBuffer"

class OutputBuffer(BaseBuffer):
    type = "OutputBuffer"
    abstract = False
    cxx_header = "vta/buffers.hh"
    cxx_class = "gem5::OutputBuffer"