import numpy as np
import pandas as pd
import os

def make_data(n, m):
    data = np.zeros((n, m))
    row_means = np.random.random(n);
    col_means = np.random.random(m);
    global_effect = np.random.random();
    for i in range(n):
        for j in range(m):
            data[i,j] = global_effect + row_means[i] + col_means[j] + np.random.normal();
    pd.DataFrame(data).to_csv('data/{}_{}'.format(n, m), index = False, header = False)
    
if __name__ == '__main__':
    os.makedirs('data', exist_ok=True)
    np.random.seed(1)
    for i in range(1, 11):
        make_data(i*100, i*100)
