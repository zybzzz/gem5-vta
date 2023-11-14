import m5
from m5.objects import *

# All SimObject initialization functions under the root tree will be called
root = Root(full_system=False)
root.vta = BaseVTA()

root.vta.hardware_version = "0.0.2"
root.vta.log_input_width = 3
root.vta.log_wight_width = 3
root.vta.log_accumulator_width = 5
root.vta.log_batch = 0
root.vta.log_block = 4
root.vta.log_micro_op_buff_size = 15
root.vta.log_input_buff_size = 15
root.vta.log_weight_buff_size = 18
root.vta.log_accumulator_buff_size = 17


m5.instantiate()

print("Beginning Simulation")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
