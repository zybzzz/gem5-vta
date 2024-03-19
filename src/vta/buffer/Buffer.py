from m5.SimObject import SimObject


class InputBuffer(SimObject):
    type = "InputBuffer"
    cxx_header = "vta/buffer/input_buffer.hh"
    cxx_class = "gem5::InputBuffer"


class OutputBuffer(SimObject):
    type = "OutputBuffer"
    cxx_header = "vta/buffer/output_buffer.hh"
    cxx_class = "gem5::OutputBuffer"


class WeightBuffer(SimObject):
    type = "WeightBuffer"
    cxx_header = "vta/buffer/weight_buffer.hh"
    cxx_class = "gem5::WeightBuffer"
