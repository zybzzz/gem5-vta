vta:
	scons build/NULL/gem5.opt -j 8

run:
	build/NULL/gem5.opt --debug-flags=BaseVTAFlag \
	 												src/vta/vta_sim_script.py

clean:
	rm -rf ./build