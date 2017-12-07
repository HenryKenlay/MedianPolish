from subprocess import call
from time import time
import numpy as np
import pandas as pd

def benchmark(prog, repeats, save = False):
    dfs = []
    for i in np.arange(100, 1100, 100):
        a, b = time_program(i, i, prog, repeats, False)
        df = pd.DataFrame({'total' : a, 'read-time' : b}, index = [i for _ in range(repeats)])
        dfs.append(df)
    df = pd.concat(dfs)
    df.index.name = 'input-size'
    if save:
        df.to_csv('results/{}.csv'.format(prog))
    return df

def time_program(n,m, prog = 'R', repeats = 100, return_means = True):
    if prog != 'R':
        program = ['./{}.out'.format(prog),]
    else:
        program = ['/usr/local/bin/Rscript', 'median_polish.R']
    prog_timings = []
    read_timings = []
    for _ in range(repeats):
        start = time()
        call(program + [str(n), str(m)])
        prog_timings.append(time() - start)
        start = time()
        call(program + [str(n), str(m), '0'])
        read_timings.append(time() - start)
    if return_means:
        return np.mean(prog_timings), np.mean(read_timings)
    else:
        return prog_timings, read_timings

if __name__ == '__main__':
    benchmark('R', 100, True)
    benchmark('median_polish-v1', 100, True)
    benchmark('median_polish-v2', 100, True)
    benchmark('median_polish-v3', 100, True)