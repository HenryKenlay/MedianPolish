from subprocess import call
from time import time
import numpy as np
import matplotlib.pyplot as plt 

def time_program(n,m, prog = "R", repeats = 100, return_means = True):
    if prog != "R":
        program = ["./{}".format(prog),]
    else:
        program = ["/usr/local/bin/Rscript", "median_polish.R"]
    prog_timings = []
    read_timings = []
    for _ in range(repeats):
        start = time()
        call(program + [str(n), str(m)])
        prog_timings.append(time() - start)
        start = time()
        call(program + [str(n), str(m), "0"])
        read_timings.append(time() - start)
    if return_means:
        return np.mean(prog_timings), np.mean(read_timings)
    else:
        return prog_timings, read_timings

#print(time_program(1000,1000, repeats = 5))
for i in np.arange(100, 1100, 100):    
    _, v2_time = time_program(i,i, './median_polish-v2.out', 20, False)
    _, v3_time = time_program(i,i, './median_polish-v3.out', 20, False)
    print(mannwhitneyu(np.asarray(v2_time), np.asarray(v3_time), alternative = 'greater'))