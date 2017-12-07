import pandas as pd
import os
import matplotlib.pyplot as plt
import numpy as np

fig, axs = plt.subplots(1, 3, sharey = True, figsize = (15, 6))
input_sizes = np.arange(100, 1100, 100)

algos = ['R', 'median_polish-v1', 'median_polish-v2', 'median_polish-v3']
colors = ['red', 'skyblue', 'deepskyblue', 'blue']

for algo, color in zip(algos, colors):
    data = pd.read_csv('results/{}.csv'.format(algo))
    read = []
    total = []
    read_std = []
    total_std = []
    for i in input_sizes:    
        subdata = data[data['input-size'] == i]
        read.append(np.mean(subdata['read-time']))
        total.append(np.mean(subdata['total']))
        read_std.append(np.std(subdata['read-time']))
        total_std.append(np.std(subdata['total']))
        
    total, read = np.asarray(total), np.asarray(read)
    axs[0].errorbar(input_sizes, total, yerr = 1.96*np.asarray(total_std), color = color, label = algo)
    axs[1].errorbar(input_sizes, read, yerr = 1.96*np.asarray(read_std), color = color, label = algo)
    std = np.sqrt(np.asarray(total_std)**2 + np.asarray(read_std)**2)
    axs[2].errorbar(input_sizes, total - read, yerr = 1.96*std, color = color, label = algo)
    

plt.tight_layout()
axs[0].set_ylabel('Time (s)')
for ax in axs:
    ax.legend(loc = 2)
    ax.set_xlabel('Square matrix dimension size')
    
axs[0].set_title('Time to read data and run algorithm')
axs[1].set_title('Time to read data')
axs[2].set_title('Time to run algorithm')

os.makedirs('figures', exist_ok = True)
plt.savefig('figures/runtimes.pdf', bbox_inches = 'tight')