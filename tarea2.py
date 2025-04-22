import numpy as np
import matplotlib.pyplot as plt

def x(t):
    return 5 + 13.4 * t - 7.36 * t**2 + 0.8 * t**3

def v(t):
    return 13.4 - 14.72 * t + 2.4 * t**2

def a(t):
    return -14.72 + 4.8 * t

# a)
t_vals = np.arange(0, 7.01, 0.01)
x_vals = x(t_vals)
v_vals = v(t_vals)
a_vals = a(t_vals)

plt.figure(figsize=(15, 4))

plt.subplot(1, 3, 1)
plt.plot(t_vals, x_vals, color='blue')
plt.title('x(t)')
plt.xlabel('t (s)')
plt.ylabel('x (m)')
plt.grid(True)

plt.subplot(1, 3, 2)
plt.plot(t_vals, v_vals, color='green')
plt.title('v(t)')
plt.xlabel('t (s)')
plt.ylabel('v (m/s)')
plt.grid(True)

plt.subplot(1, 3, 3)
plt.plot(t_vals, a_vals, color='red')
plt.title('a(t)')
plt.xlabel('t (s)')
plt.ylabel('a (m/s²)')
plt.grid(True)

plt.tight_layout()
plt.show()

def encontrar_intervalos(condicion, etiqueta):
    print(f"\n{etiqueta}:")
    activo = False
    inicio = 0
    for i in range(len(t_vals)):
        if condicion(i) and not activo:
            inicio = t_vals[i]
            activo = True
        elif not condicion(i) and activo:
            fin = t_vals[i]
            print(f"  desde t = {inicio:.2f}s hasta t = {fin:.2f}s")
            activo = False
    if activo:
        fin = t_vals[-1]
        print(f"  desde t = {inicio:.2f}s hasta t = {fin:.2f}s")

# b)
encontrar_intervalos(lambda i: x_vals[i] > 0, "b) x > 0")
# c)
encontrar_intervalos(lambda i: x_vals[i] < 0, "c) x < 0")
# d)
encontrar_intervalos(lambda i: v_vals[i] > 0, "d) movimiento hacia +x")
# e)
encontrar_intervalos(lambda i: v_vals[i] < 0, "e) movimiento hacia -x")
# f)
encontrar_intervalos(lambda i: a_vals[i] > 0, "f) velocidad aumentando")
# g)
encontrar_intervalos(lambda i: a_vals[i] < 0, "g) velocidad disminuyendo")
# h)
encontrar_intervalos(lambda i: v_vals[i] * a_vals[i] > 0, "h) rapidez aumentando")
# i)
encontrar_intervalos(lambda i: v_vals[i] * a_vals[i] < 0, "i) rapidez disminuyendo")