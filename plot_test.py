import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv('./dados/fb_0.dat', sep='\s+', header=None)
data = pd.DataFrame(data) 

x = data[0]
y = data[1]

plt.plot(x, y, 'r--')

plt.show()