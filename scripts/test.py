#!/usr/bin/env python2
"""
Description.

"""
from __future__ import division
import os
import numpy as np
from matplotlib import pyplot

varia_dir = os.path.dirname(os.path.dirname(os.sys.argv[0]))
data_file = os.path.join(varia_dir, "data", "mnist_abridged.txt")

mnist = np.loadtxt(data_file, dtype=int, delimiter=',').reshape(-1, 28, 28)
index = np.random.randint(len(mnist))

print("Showing sample {0} from \"{1}\".".format(index, os.path.basename(data_file)))
print("Close plot to finish.")

pyplot.imshow(mnist[index])
pyplot.show()
