# gem5-vta

## Working directories and environment

```
src/vta         # main work directory, all modeling files are in this directory
configs/vta     # The vta script and configuration files are in this directory
```

**python version 3.8 and tvm-vta version is 0.15.dev0.**

## Compile and run

to compile:

```shell
scons build/NULL/gem5.opt -j 8
```

to run:

```shell
build/NULL/gem5.opt configs/vta/vta_sim_script.py
```

## Tips for this git repository

1. The working directory is listed above, if you add a new working directory, please change the README and raise pr.
2. **Please use English throughout the project, whether you are submitting a commit or adding comments to a file,
   otherwise encoding errors will result.**
3. When making changes to the project, do so on your own branch. If you are done, you can raise pr.
4. Use github issue for discussion.
5. When submitting a commit, it must conform to the rules for writing commit messages proposed by the gem5 project.

## Common error And solution

E: Can't find python installation.
A: Check your python environment. If your python installs correctly, delete the build directory and recompile.

## Project development phase

research related papers(done) -> vta basic module modeling(done) -> modeling for correctness(active) -> optimize
modeling accuracy

## Script examples and what gem5-vta is doing now

```python
# reference to configs/vta/vta_sim_script.py
import m5
from m5.objects import *

############################################################
####define XBar and port to communicate with vta model######

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

############################################################

vta = BaseVTA()  # create vta model

vta.instruction_port = system.membus.cpu_side_ports
vta.micro_op_port = system.membus.cpu_side_ports
vta.data_port = system.membus.cpu_side_ports

root = Root(full_system=False, system=system, vta=vta)

m5.instantiate()

print("Beginning Simulation")
exit_event = m5.simulate()
print(f"Exiting @ tick {m5.curTick()} because {exit_event.getCause()}")

```

Our current work is still modeling the modules of vta and modeling correctness. Current work does not yet involve
interaction with the host side.

# The gem5 Simulator

This is the repository for the gem5 simulator. It contains the full source code
for the simulator and all tests and regressions.

The gem5 simulator is a modular platform for computer-system architecture
research, encompassing system-level architecture as well as processor
microarchitecture. It is primarily used to evaluate new hardware designs,
system software changes, and compile-time and run-time system optimizations.

The main website can be found at <http://www.gem5.org>.

## Getting started

A good starting point is <http://www.gem5.org/about>, and for
more information about building the simulator and getting started
please see <http://www.gem5.org/documentation> and
<http://www.gem5.org/documentation/learning_gem5/introduction>.

## Building gem5

To build gem5, you will need the following software: g++ or clang,
Python (gem5 links in the Python interpreter), SCons, zlib, m4, and lastly
protobuf if you want trace capture and playback support. Please see
<http://www.gem5.org/documentation/general_docs/building> for more details
concerning the minimum versions of these tools.

Once you have all dependencies resolved, execute
`scons build/ALL/gem5.opt` to build an optimized version of the gem5 binary
(`gem5.opt`) containing all gem5 ISAs. If you only wish to compile gem5 to
include a single ISA, you can replace `ALL` with the name of the ISA. Valid
options include `ARM`, `NULL`, `MIPS`, `POWER`, `SPARC`, and `X86` The complete
list of options can be found in the build_opts directory.

See https://www.gem5.org/documentation/general_docs/building for more
information on building gem5.

## The Source Tree

The main source tree includes these subdirectories:

* build_opts: pre-made default configurations for gem5
* build_tools: tools used internally by gem5's build process.
* configs: example simulation configuration scripts
* ext: less-common external packages needed to build gem5
* include: include files for use in other programs
* site_scons: modular components of the build system
* src: source code of the gem5 simulator. The C++ source, Python wrappers, and Python standard library are found in this
  directory.
* system: source for some optional system software for simulated systems
* tests: regression tests
* util: useful utility programs and files

## gem5 Resources

To run full-system simulations, you may need compiled system firmware, kernel
binaries and one or more disk images, depending on gem5's configuration and
what type of workload you're trying to run. Many of these resources can be
obtained from <https://resources.gem5.org>.

More information on gem5 Resources can be found at
<https://www.gem5.org/documentation/general_docs/gem5_resources/>.

## Getting Help, Reporting bugs, and Requesting Features

We provide a variety of channels for users and developers to get help, report
bugs, requests features, or engage in community discussions. Below
are a few of the most common we recommend using.

* **GitHub Discussions**: A GitHub Discussions page. This can be used to start
  discussions or ask questions. Available at
  <https://github.com/orgs/gem5/discussions>.
* **GitHub Issues**: A GitHub Issues page for reporting bugs or requesting
  features. Available at <https://github.com/gem5/gem5/issues>.
* **Jira Issue Tracker**: A Jira Issue Tracker for reporting bugs or requesting
  features. Available at <https://gem5.atlassian.net/>.
* **Slack**: A Slack server with a variety of channels for the gem5 community
  to engage in a variety of discussions. Please visit
  <https://www.gem5.org/join-slack> to join.
* **gem5-users@gem5.org**: A mailing list for users of gem5 to ask questions
  or start discussions. To join the mailing list please visit
  <https://www.gem5.org/mailing_lists>.
* **gem5-dev@gem5.org**: A mailing list for developers of gem5 to ask questions
  or start discussions. To join the mailing list please visit
  <https://www.gem5.org/mailing_lists>.

## Contributing to gem5

We hope you enjoy using gem5. When appropriate we advise charing your
contributions to the project. <https://www.gem5.org/contributing> can help you
get started. Additional information can be found in the CONTRIBUTING.md file.
