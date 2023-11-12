import m5
from m5.objects import *

# All SimObject initialization functions under the root tree will be called
root = Root(full_system = False)
root.vta = BaseVTA()

root.vta.HW_VER = "0.0.2"
root.vta.LOG_INP_WIDTH = 3
root.vta.LOG_WGT_WIDTH = 3
root.vta.LOG_ACC_WIDTH = 5
root.vta.LOG_BATCH = 0
root.vta.LOG_BLOCK = 4
root.vta.LOG_UOP_BUFF_SIZE = 15
root.vta.LOG_INP_BUFF_SIZE = 15
root.vta.LOG_WGT_BUFF_SIZE = 18
root.vta.LOG_ACC_BUFF_SIZE = 17




m5.instantiate()

print("Beginning Simulation")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")