import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.special import factorial
import scipy.optimize as opt

def approx_curve(x, a, c) :
    return (x * a)*factorial(x) + c

def held_curva(x, a, b, c):
    return ((x*a)**2) * (2**(x * b)) + c

data = pd.read_csv('./dados/fb_0.dat',sep='\s+',header=None)
data = pd.DataFrame(data) 

held_data = pd.read_csv('./dados/held.dat',sep='\s+',header=None)
held_data = pd.DataFrame(held_data)

x_h = held_data[0]
y_h = held_data[1]

x = data[0]
y = data[1]

fig, ax = plt.subplots()

ax.set_xlabel("Quantidade de cidades")
ax.set_ylabel("Tempo de processamento em segundos")
ax.text(11, 20, "n*n!")
#ax.text(11.5, 1, "n² * 2^n")

plt.plot(x, y, color='red', marker='o', linestyle='dashed', linewidth=1, markersize=4)
#plt.plot(x_h, y_h, color='purple', marker='o', linestyle='dashed', linewidth=1, markersize=4)

new_fator, _ = opt.curve_fit(held_curva, x_h, y_h)
n_a, n_b, n_c = new_fator

m_fator, _ = opt.curve_fit(approx_curve, x, y);
v_a, v_c = m_fator

print("{} {}".format(v_a, v_c))
print("{} {} {}".format(n_a, n_b, n_c))
approximacao_dominio = np.linspace(2, 12, 100)

plt.plot(approximacao_dominio, approx_curve(approximacao_dominio, v_a, v_c), color='green')
#plt.plot(approximacao_dominio, held_curva(approximacao_dominio, n_a, n_b, n_c), color='blue')

plt.show()