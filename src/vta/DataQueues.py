from m5.params import *
from m5.SimObject import SimObject

class BaseDataQueue(SimObject):
    type = "BaseDataQueue"
    abstract = True
    cxx_header = "vta/base_data_queue.hh"
    cxx_class = "gem5::BaseDataQueue"

class CMP2STQueue(BaseDataQueue):
    type = "CMP2STQueue"
    abstract = False
    cxx_header = "vta/data_queues.hh"
    cxx_class = "gem5::CMP2STQueue"

class ST2CMPQueue(BaseDataQueue):
    type = "ST2CMPQueue"
    abstract = False
    cxx_header = "vta/data_queues.hh"
    cxx_class = "gem5::ST2CMPQueue"

class CMP2LDQueue(BaseDataQueue):
    type = "CMP2LDQueue"
    abstract = False
    cxx_header = "vta/data_queues.hh"
    cxx_class = "gem5::CMP2LDQueue"

class LD2CMPQueue(BaseDataQueue):
    type = "LD2CMPQueue"
    abstract = False
    cxx_header = "vta/data_queues.hh"
    cxx_class = "gem5::LD2CMPQueue"