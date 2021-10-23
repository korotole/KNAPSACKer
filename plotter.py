import sys

import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
from matplotlib.ticker import AutoMinorLocator
from matplotlib import gridspec


#read 4th column of csv file
time = []         #an empty list to store the second column
with open(sys.argv[1], 'r') as rf:
    reader = csv.reader(rf, delimiter=' ')
    for row in reader:
      time.append(round(int(row[3])))

fig, ax = plt.subplots(1, figsize=(16,6))

# ec=       color
# bins=     bins formation
# range=    range of bins shown (no effect if bins are sequence)
# density=  raw_count/(totalCount * bin width) {% of being inside the bin comparely to all possible values}
n, bins, pathces = plt.hist(time, bins=100)


# define minor ticks and draw a grid with them
minor_locator = AutoMinorLocator(2)
plt.gca().xaxis.set_minor_locator(minor_locator)
plt.grid(which='minor', color='white', lw = 0.5)
# x ticks
xticks = [(bins[idx+1] + value)/2 for idx, value in enumerate(bins[:-1])]
xticks_labels = [ "{:.0f}-{:.0f}".format(value, bins[idx+1]) for idx, value in enumerate(bins[:-1])]
plt.xticks(xticks, labels = xticks_labels, rotation="vertical", fontsize=10)

# remove y ticks
plt.yticks([])

# remove major and minor ticks from the x axis, but keep the labels
ax.tick_params(axis='x', which='both',length=0)
# Hide the right and top spines
ax.spines['bottom'].set_visible(False)
ax.spines['left'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)

# plot values on top of bars
for idx, value in enumerate(n):
    if value > 0:
        plt.text(xticks[idx], value + 1, int(value), ha='center', fontsize=8, fontweight="bold")

plt.xlabel("min: " + sys.argv[2] + "    max: " + sys.argv[3] + "    ave: " + sys.argv[4] + "\nmiliseconds", fontsize=12)
plt.ylabel("count", fontsize=12)
plt.title(sys.argv[1] + "\n", fontsize=18)

plt.tight_layout()
plt.savefig(sys.argv[1] + ".png")
