import m5
from m5.objects import *

system = System()

system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "1GHz"
system.clk_domain.voltage_domain = VoltageDomain()

system.membus = SystemXBar()
system.mem_ranges = [AddrRange("2GB")]
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR4_2400_4x16()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports
system.system_port = system.membus.cpu_side_ports

vta = BaseVTA()

vta.instruction_port = system.membus.cpu_side_ports
vta.micro_op_port = system.membus.cpu_side_ports
vta.data_port = system.membus.cpu_side_ports

root = Root(full_system=False, system=system, vta=vta)

m5.instantiate()

print("Beginning Simulation")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")
