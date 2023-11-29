#!/bin/python
from os import system

num_of_cores = int(input("Número de cores do seu CPU: "))
num_of_cores -= 1 # likwid conta a partir do 0

likwid_metrics = {
  "flops": {
    "metric": "FLOPS_DP",
    "label": "AVX DP [MFLOP/s]",
  },
  "l2cache": {
    "metric": "L2CACHE",
    "label": "ratio",
  },
  "mem": {
    "metric": "MEM",
    "label": "Memory bandwidth [MBytes/s]",
  },
}

likwid_markers = ["generate_matrix", "solve_system", "residue"]

sample_inputs = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 100_000, 1_000_000, 10_000_000, 100_000_000]  

system(f"echo \"performance\" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor")    
system("gcc gera_entrada.c -o gera_entrada")
system("make")
system("mkdir results")

def get_metric_number_from_file(filename, metric):
    tracked_metrics = {}
    current_marker = None

    with open(filename, 'r') as f:
        for line in f:
            for markers in likwid_markers:
                if markers in line:
                    current_marker = markers
            if metric in line:
                if current_marker is None:
                    raise Exception(f"Marker não encontrado para a métrica {metric}")

                tracked_metrics[current_marker] = (line.split('|')[-2].strip())
    
    return tracked_metrics

def get_runtime_from_file(filename):
    runtimes = {}

    with open(filename, 'r') as f:
        for line in f:
            if "tempo de execucoes" in line:
                for i in range(3):
                    runtimes[likwid_markers[i]] = (next(f).strip())


    return runtimes
  
for i in sample_inputs:
    for metric in likwid_metrics:
        system(f"./gera_entrada {i} | likwid-perfctr -C {num_of_cores} -g {likwid_metrics[metric]['metric']} -m ./ajustePol > {metric}_tmp.txt")

        tracked_metrics = get_metric_number_from_file(f"{metric}_tmp.txt", likwid_metrics[metric]['label'])

        for marker in tracked_metrics:
            with open(f"./results/{metric}_{marker}.txt", 'a') as f:
                f.write(f"{i} {tracked_metrics[marker]}\\\\\n")
  

    runtimes = get_runtime_from_file(f"{metric}_tmp.txt")

    for marker in runtimes:
        with open(f"./results/runtime_{marker}.txt", 'a') as f:
            f.write(f"{i} {runtimes[marker]}\\\\\n")


system("make clean")
system(f"rm gera_entrada")
system(f"rm *_tmp.txt")
system(f"echo \"powersave\" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor") 
print('Done!')