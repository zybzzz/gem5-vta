import matplotlib.pyplot as plt

# 数据准备
cpus = ["Host CPU", "Atomic CPU", "Timing CPU", "O3CPU"]

# 第一张图的数据
run_times_ns = [684904, 6651198, 12225086, 2384781]
# 将纳秒转换为毫秒以便于展示
run_times_ms = [time / 1000000 for time in run_times_ns]

# 第二张图的数据
sim_times_s = [7.68, 10.82, 45.48]

# 计算第一张图中的每个数据与 Host CPU 的误差百分比
# 误差百分比 = ((其他 CPU 时间 - Host CPU 时间) / Host CPU 时间) * 100
host_cpu_time = run_times_ms[0]
error_percentages = [
    (time - host_cpu_time) / host_cpu_time * 100 for time in run_times_ms
]

# 重新绘制第一张图，包括误差百分比
fig, axs = plt.subplots(2, 1, figsize=(10, 10))

# 绘制运行时间对比图
axs[0].bar(cpus, run_times_ms)
axs[0].set_title("Running Time Comparison")
axs[0].set_xlabel("CPU type")
axs[0].set_ylabel("running time (ms)")
axs[0].set_xticks(cpus)

# 在每个条形上添加误差百分比
for i, error in enumerate(error_percentages):
    axs[0].text(i, run_times_ms[i], f"{error:.2f}%", ha="center", va="bottom")

# 绘制模拟时间对比图（排除了 "Host CPU"）
axs[1].bar(cpus[1:], sim_times_s)
axs[1].set_title("Simulation Time Comparison")
axs[1].set_xlabel("CPU type")
axs[1].set_ylabel("simulation time (s)")
axs[1].set_xticks(cpus[1:])

# 显示图表
plt.tight_layout()
plt.show()
