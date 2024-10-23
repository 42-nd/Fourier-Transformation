# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('data.csv', delimiter=',', skip_header=1)

indices = data[:, 0]
original_data = data[:, 1]
filtered_data = data[:, 2]

fig, axs = plt.subplots(2, 2, figsize=(12, 10))

axs[0, 0].plot(indices, original_data, label='Original Data', linestyle='-', color='blue', alpha=0.7)
axs[0, 0].set_title("Continuous Plot of Original Data")
axs[0, 0].set_xlabel("Index")
axs[0, 0].set_ylabel("Amplitude")
axs[0, 0].grid(True)

axs[0, 1].plot(indices, filtered_data, label='Filtered Data', linestyle='-', color='red', alpha=0.7)
axs[0, 1].set_title("Continuous Plot of Filtered Data")
axs[0, 1].set_xlabel("Index")
axs[0, 1].set_ylabel("Amplitude")
axs[0, 1].grid(True)

axs[1, 0].scatter(indices, original_data, label='Original Data', color='blue', alpha=0.7)
axs[1, 0].set_title("Scatter Plot of Original Data")
axs[1, 0].set_xlabel("Index")
axs[1, 0].set_ylabel("Amplitude")
axs[1, 0].grid(True)

axs[1, 1].scatter(indices, filtered_data, label='Filtered Data', color='red', alpha=0.7)
axs[1, 1].set_title("Scatter Plot of Filtered Data")
axs[1, 1].set_xlabel("Index")
axs[1, 1].set_ylabel("Amplitude")
axs[1, 1].grid(True)

plt.tight_layout()
plt.show()

