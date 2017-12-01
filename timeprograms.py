from subprocess import call
from time import time
import numpy as np
import matplotlib.pyplot as plt 

def time_program(n,m, C = True, repeats = 100):
    data_file = '{}_{}'.format(n, m)
    if C:
        program = ["./median_polish.out",]
    else:
        program = ["/usr/local/bin/Rscript", "median_polish.R"]
    prog_timings = []
    read_timings = []
    for _ in range(repeats):
        start = time()
        call(program + [data_file])
        prog_timings.append(time() - start)
        start = time()
        call(program + [data_file, "0"])
        read_timings.append(time() - start)
    return np.mean(prog_timings), np.mean(read_timings)

C_prog = []
C_read = []
R_prog = []
R_read = []
for i in np.arange(100, 1100, 100):
    a, b = time_program(i, i, True, 10)
    C_prog.append(a)
    C_read.append(b)
    a, b = time_program(i, i, False, 10)
    R_prog.append(a)
    R_read.append(b)
    
C_prog = np.asarray(C_prog)
C_read = np.asarray(C_read)
R_prog = np.asarray(R_prog)
R_read = np.asarray(R_read)

plt.plot(C_prog, 'r--')
plt.plot(C_read, 'r:')
plt.plot(C_prog - C_read, 'r')
plt.plot(R_prog, 'b--')
plt.plot(R_read, 'b:')
plt.plot(R_prog - R_read, 'b')
