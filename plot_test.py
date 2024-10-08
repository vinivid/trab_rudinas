import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.special import factorial
import scipy.optimize as opt

def approx_curve(x, a, c) :
    return (x * a)*factorial(x) + c

data = pd.read_csv('./dados/fb_0.dat',sep='\s+',header=None)
data = pd.DataFrame(data) 

x = data[0]
y = data[1]

fig, ax = plt.subplots()

ax.set_xlabel("Quantidade de cidades")
ax.set_ylabel("Tempo de processamento em segundos")
ax.text(9, 20, "3*(10^-9)*n*n! + 0.02")

plt.plot(x, y, color='red', marker='o', linestyle='dashed', linewidth=1, markersize=4)

m_fator, _ = opt.curve_fit(approx_curve, x, y);
v_a, v_c = m_fator

print("{} {}".format(v_a, v_c))
approximacao_dominio = np.linspace(2, 12, 100)

plt.plot(approximacao_dominio, approx_curve(approximacao_dominio, v_a, v_c), color='green')

plt.show()