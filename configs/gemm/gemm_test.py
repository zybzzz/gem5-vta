from m5 import *
from m5.objects import *
import argparse
import os


class L1Cache(Cache):
    size = "32kB"
    assoc = 8
    tag_latency = 2
    data_latency = 2
    response_latency = 2
    mshrs = 4
    tgts_per_mshr = 20


class L1_ICache(L1Cache):
    is_read_only = True
    # Writeback clean lines as well
    writeback_clean = True


class L1_DCache(L1Cache):
    pass


class L2Cache(Cache):
    size = "512kB"
    assoc = 16
    tag_latency = 5
    data_latency = 5
    response_latency = 5
    mshrs = 20
    tgts_per_mshr = 12
    write_buffers = 16


class L3Cache(Cache):
    size = "2MB"
    assoc = 16
    tag_latency = 7
    data_latency = 7
    response_latency = 7
    mshrs = 32
    tgts_per_mshr = 20
    write_buffers = 32


class L3XBar(L2XBar):
    pass


parser = argparse.ArgumentParser()
parser.add_argument("--cpu_type", type=str, help="cpu type")
options = parser.parse_args()

system = System()

if options.cpu_type == "atomic":
    system.cpu = AtomicSimpleCPU()
    system.mem_mode = "atomic"
elif options.cpu_type == "timing":
    system.cpu = TimingSimpleCPU()
    system.mem_mode = "timing"
elif options.cpu_type == "o3":
    system.cpu = O3CPU()
    system.mem_mode = "timing"
else:
    system.cpu = AtomicSimpleCPU()
    system.mem_mode = "atomic"

# system.cpu = O3CPU()

# clock
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = "3.9GHz"
system.clk_domain.voltage_domain = VoltageDomain()

# cache
system.icache = L1_ICache()
system.dcache = L1_DCache()
system.l2cache = L2Cache()
system.l3cache = L3Cache()

# memory
system.mem_ranges = [AddrRange("512MB")]
system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR4_2400_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]

# xbar
system.l2bus = L2XBar()
system.l3bus = L3XBar()
system.membus = SystemXBar()

# connect components
system.icache.cpu_side = system.cpu.icache_port
system.dcache.cpu_side = system.cpu.dcache_port
system.icache.mem_side = system.l2bus.cpu_side_ports
system.dcache.mem_side = system.l2bus.cpu_side_ports
system.l2cache.cpu_side = system.l2bus.mem_side_ports
system.l2cache.mem_side = system.l3bus.cpu_side_ports
system.l3cache.cpu_side = system.l3bus.mem_side_ports
system.l3cache.mem_side = system.membus.cpu_side_ports
system.mem_ctrl.port = system.membus.mem_side_ports

# intr
system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.master
system.cpu.interrupts[0].int_master = system.membus.slave
system.cpu.interrupts[0].int_slave = system.membus.master

# run script
thispath = os.path.dirname(os.path.realpath(__file__))
binary = os.path.join(
    thispath,
    "gemm.out",
)
system.workload = SEWorkload.init_compatible(binary)

process = Process()
process.cmd = [binary]
system.cpu.workload = process
system.cpu.createThreads()

root = Root(full_system=False, system=system)
m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print("Exiting @ tick %i because %s" % (m5.curTick(), exit_event.getCause()))
