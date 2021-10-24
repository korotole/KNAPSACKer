from numpy import dtype
import sys
import pandas as pd
from matplotlib import pyplot as plt
import itertools

import warnings
from pandas.core.common import SettingWithCopyWarning
warnings.simplefilter(action="ignore", category=SettingWithCopyWarning)

plt.style.use("seaborn")
fig, ax = plt.subplots(1, figsize=(40,15))

d0NR = pd.read_csv(sys.argv[1], sep=" ", header=None, names=["d0NRfiles", "d0NRmin", "d0NRmax", "d0NRave"])
d1NR = pd.read_csv(sys.argv[2], sep=" ", header=None, names=["d1NRfiles", "d1NRmin", "d1NRmax", "d1NRave"])
d0ZR = pd.read_csv(sys.argv[3], sep=" ", header=None, names=["d0ZRfiles", "d0ZRmin", "d0ZRmax", "d0ZRave"])
d1ZR = pd.read_csv(sys.argv[4], sep=" ", header=None, names=["d1ZRfiles", "d1ZRmin", "d1ZRmax", "d1ZRave"])

sizes = [ 20, 22, 25, 27, 30, 32 ]   # 4 10 20    # 35 37 40

d0NRmins = d0NR["d0NRmin"]
d0NRmins[:] = [int(x / 1000) for x in d0NRmins]
d0NRmaxs = d0NR["d0NRmax"]
d0NRmaxs[:] = [int(x / 1000) for x in d0NRmaxs]
d0NRaves = d0NR["d0NRave"]
d0NRaves[:] = [int(x / 1000) for x in d0NRaves]

d1NRmins = d1NR["d1NRmin"]
d1NRmins[:] = [int(x / 1000) for x in d1NRmins]
d1NRmaxs = d1NR["d1NRmax"]
d1NRmaxs[:] = [int(x / 1000) for x in d1NRmaxs]
d1NRaves = d1NR["d1NRave"]
d1NRaves[:] = [int(x / 1000) for x in d1NRaves]

d0ZRmins = d0ZR["d0ZRmin"]
d0ZRmins[:] = [int(x / 1000) for x in d0ZRmins]
d0ZRmaxs = d0ZR["d0ZRmax"]
d0ZRmaxs[:] = [int(x / 1000) for x in d0ZRmaxs]
d0ZRaves = d0ZR["d0ZRave"]
d0ZRaves[:] = [int(x / 1000) for x in d0ZRaves]

d1ZRmins = d1ZR["d1ZRmin"]
d1ZRmins[:] = [int(x / 1000) for x in d1ZRmins]
d1ZRmaxs = d1ZR["d1ZRmax"]
d1ZRmaxs[:] = [int(x / 1000) for x in d1ZRmaxs]
d1ZRaves = d1ZR["d1ZRave"]
d1ZRaves[:] = [int(x / 1000) for x in d1ZRaves]

plt.plot(sizes, d0NRaves[3:], label="d0NRave", color="green")
plt.plot(sizes, d0NRmins[3:], label="d0NRmin", color="blue")
plt.plot(sizes, d0NRmaxs[3:], label="d0NRmax", color="red")

plt.plot(sizes, d1NRaves[3:-3], label="d1NRave", linestyle="dashed", color="green")
plt.plot(sizes, d1NRmins[3:-3], label="d1NRmin", linestyle="dashed", color="blue")
plt.plot(sizes, d1NRmaxs[3:-3], label="d1NRmax", linestyle="dashed", color="red")

plt.plot(sizes, d0ZRaves[3:], label="d0ZRave", linestyle="dotted", color="green")
plt.plot(sizes, d0ZRmins[3:], label="d0ZRmin", linestyle="dotted", color="blue")
plt.plot(sizes, d0ZRmaxs[3:], label="d0ZRmax", linestyle="dotted", color="red")

plt.plot(sizes, d1ZRaves[3:-2], label="d1ZRave", linestyle="dashdot", color="green")
plt.plot(sizes, d1ZRmins[3:-2], label="d1ZRmin", linestyle="dashdot", color="blue")
plt.plot(sizes, d1ZRmaxs[3:-2], label="d1ZRmax", linestyle="dashdot", color="red")

plt.legend(fontsize=24)

# times = d1ZRmins + d1ZRaves + d1ZRmaxs + d0ZRmins + d0ZRaves + d0ZRmaxs + d1NRmins + d1NRaves + d1NRmaxs + d0NRmins + d0NRaves + d0NRmaxs

plt.title("COMBINED", fontsize=28)

plt.xticks(sizes, sizes, fontsize=20)
plt.yticks(fontsize=20)

plt.xlabel("KNAPSACK SIZE", fontsize=22)
plt.ylabel("SECONDS", fontsize=22)

# print(times)

# plt.show()

plt.savefig("all.png")