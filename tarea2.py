import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fsolve

def x(t):
    return 5 + 13.4*t - 7.36*t**2 + 0.8*t**3

def v(t):
    return 13.4 - 14.72*t + 2.4*t**2

def a(t):
    return -14.72 + 4.8*t

def buscar():
    roots = []
    for i in np.arange(0, 7, 0.1):
        try:
            root = fsolve(x, i)[0]
            if 0 <= root <= 7 and not any(np.isclose(root, r, atol=1e-3) for r in roots):
                roots.append(root)
        except:
            continue
    return sorted(roots)

def mov_dir():
    v_roots = []
    for i in np.arange(0, 7, 0.1):
        try:
            root = fsolve(v, i)[0]
            if 0 <= root <= 7 and not any(np.isclose(root, r, atol=1e-3) for r in v_roots):
                v_roots.append(root)
        except:
            continue
    return sorted(v_roots)

t = np.linspace(0, 7, 500)
plt.figure(figsize=(15, 5))

def velocidad():
    a_roots = []
    for i in np.arange(0, 7, 0.1):
        try:
            root = fsolve(a, i)[0]
            if 0 <= root <= 7 and not any(np.isclose(root, r, atol=1e-3) for r in a_roots):
                a_roots.append(root)
        except:
            continue
    return sorted(a_roots)

def intervalos(roots, func, condition):
    intervals = []
    roots = [0] + roots + [7]
    for i in range(len(roots)-1):
        t_test = (roots[i] + roots[i+1])/2
        if condition(func(t_test)):
            intervals.append((roots[i], roots[i+1]))
    return intervals

def cambio_Vel():
    critical = sorted(list(set(v_roots + a_roots)))
    intervals = []
    critical = [0] + critical + [7]
    for i in range(len(critical)-1):
        t_test = (critical[i] + critical[i+1])/2
        v_val = v(t_test)
        a_val = a(t_test)
        if v_val * a_val > 0:
            intervals.append((critical[i], critical[i+1]))
    return intervals

def disminuye():
    critical = sorted(list(set(v_roots + a_roots)))
    intervals = []
    critical = [0] + critical + [7]
    for i in range(len(critical)-1):
        t_test = (critical[i] + critical[i+1])/2
        v_val = v(t_test)
        a_val = a(t_test)
        if v_val * a_val < 0:
            intervals.append((critical[i], critical[i+1]))
    return intervals

plt.subplot(1, 3, 1)
plt.plot(t, x(t))
plt.title('x - t')
plt.xlabel('t (s)')
plt.ylabel('x (m)')
plt.grid()

plt.subplot(1, 3, 2)
plt.plot(t, v(t))
plt.title('v - t')
plt.xlabel('t (s)')
plt.ylabel('v (m/s)')
plt.grid()

plt.subplot(1, 3, 3)
plt.plot(t, a(t))
plt.title('a - t')
plt.xlabel('t (s)')
plt.ylabel('a (m/s²)')
plt.grid()

plt.tight_layout()
plt.show()

roots = buscar()
print(f"Raices: {roots}")

v_roots = mov_dir()
print(f"Tiempos donde v(t) = 0: {v_roots}")

a_roots = velocidad()
print(f"Tiempos donde a(t) = 0: {a_roots}")

print("\n(b) Intervalos donde x(t) > 0:", intervalos(roots, x, lambda val: val > 0))
print("(c) Intervalos donde x(t) < 0:", intervalos(roots, x, lambda val: val < 0))
print("(d) Movimiento dirección positiva (v(t) > 0):", intervalos(v_roots, v, lambda val: val > 0))
print("(e) Movimiento dirección negativa (v(t) < 0):", intervalos(v_roots, v, lambda val: val < 0))
print("(f) Velocidad aumentando (a(t) > 0):", intervalos(a_roots, a, lambda val: val > 0))
print("(g) Velocidad disminuyendo (a(t) < 0):", intervalos(a_roots, a, lambda val: val < 0))
print("(h) Rapidez aumentando:", cambio_Vel())
print("(i) Rapidez disminuyendo:", disminuye())