import numpy as np
import pandas as pd

n = 5
m = 6

data = np.zeros((n, m))
row_means = np.random.random(n)*10;
col_means = np.random.random(m)*10;
for i in range(n):
    for j in range(m):
        data[i,j] = row_means[i] + col_means[j] + np.random.normal();

pd.DataFrame(data).to_csv('data/{}_{}'.format(n, m), index = False, header = False)