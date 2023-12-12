build/X86/gem5.opt --outdir='configs/gemm/atomic' configs/gemm/gemm_test.py --cpu_type='atomic'
build/X86/gem5.opt --outdir='configs/gemm/timing' configs/gemm/gemm_test.py --cpu_type='timing'
build/X86/gem5.opt --outdir='configs/gemm/o3' configs/gemm/gemm_test.py --cpu_type='o3'
