import m5
from m5.objects import *

# All SimObject initialization functions under the root tree will be called
root = Root(full_system=False)
root.vta = BaseVTA()

root.membus = SystemXBar()

# Create a DDR4 memory controller and connect it to the membus
root.mem_ctrl = MemCtrl()
root.mem_ctrl.dram = DDR4_2400_4x16()
root.mem_ctrl.dram.range = AddrRange("2GB")
root.mem_ctrl.port = root.membus.mem_side_ports

root.vta.hardware_version = "0.0.2"

root.vta.instruction_port = root.membus.cpu_side_ports
root.vta.micro_op_port = root.membus.cpu_side_ports
root.vta.data_port = root.membus.cpu_side_ports

m5.instantiate()

print("Beginning Simulation")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
