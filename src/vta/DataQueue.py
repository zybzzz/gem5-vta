from m5.params import *
from m5.SimObject import SimObject


class DataQueue(SimObject):
    type = "DataQueue"
    cxx_header = "vta/data_queue.hh"
    cxx_class = "gem5::DataQueue"
