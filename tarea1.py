import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# (a)
def polar_a_cartesianas(magnitud, direccion):
    direccion_rad = np.radians(direccion)
    x = magnitud * np.cos(direccion_rad)
    y = magnitud * np.sin(direccion_rad)
    return x, y

# (b)
def cartesianas_a_polar(x, y):
    magnitud = np.sqrt(x**2 + y**2)
    direccion = np.degrees(np.arctan2(y, x))
    return magnitud, direccion

# (c)
def suma_vectores(magnitudes, direcciones):
    x_total, y_total = 0, 0
    for mag, dir in zip(magnitudes, direcciones):
        x, y = polar_a_cartesianas(mag, dir)
        x_total += x
        y_total += y
    magnitud_res, direccion_res = cartesianas_a_polar(x_total, y_total)
    return x_total, y_total, magnitud_res, direccion_res

# (d)
def angulo_entre_vectores(v1, v2):
    dot_product = np.dot(v1, v2)
    norm_v1 = np.linalg.norm(v1)
    norm_v2 = np.linalg.norm(v2)
    cos_theta = dot_product / (norm_v1 * norm_v2)
    return np.degrees(np.arccos(cos_theta))

# (e)
def area_paralelogramo(v1, v2):
    cross_product = np.cross(v1, v2)
    return np.linalg.norm(cross_product)

def graficar_vectores_2d(vectores, titulo):
    plt.figure()
    for v in vectores:
        plt.quiver(0, 0, v[0], v[1], angles='xy', scale_units='xy', scale=1, color=np.random.rand(3,))
    plt.xlim(-10, 10)
    plt.ylim(-10, 10)
    plt.grid()
    plt.title(titulo)
    plt.show()

def graficar_vectores_3d(vectores, titulo):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    for v in vectores:
        ax.quiver(0, 0, 0, v[0], v[1], v[2], color=np.random.rand(3,))
    ax.set_xlim([-5, 5])
    ax.set_ylim([-5, 5])
    ax.set_zlim([-5, 5])
    ax.set_title(titulo)
    plt.show()

if __name__ == "__main__":
    # (a) 
    magnitud, direccion = 5, 45  # 45 grados
    x, y = polar_a_cartesianas(magnitud, direccion)
    print(f"(a) Coordenadas cartesianas: ({x:.2f}, {y:.2f})")
    graficar_vectores_2d([(x, y)], "Vector en 2D")

    # (b) 
    x, y = 3, 4
    magnitud, direccion = cartesianas_a_polar(x, y)
    print(f"(b) Magnitud: {magnitud:.2f}, Dirección: {direccion:.2f}°")

    # (c) 
    magnitudes = [2, 3, 4]
    direcciones = [30, 90, 150]
    x_res, y_res, mag_res, dir_res = suma_vectores(magnitudes, direcciones)
    print(f"(c) Resultante: ({x_res:.2f}, {y_res:.2f}), Magnitud: {mag_res:.2f}, Dirección: {dir_res:.2f}°")
    graficar_vectores_2d([polar_a_cartesianas(mag, dir) for mag, dir in zip(magnitudes, direcciones)] + [(x_res, y_res)], "Suma de tres vectores")

    # (d) 
    v1 = np.array([1, 0, 0])
    v2 = np.array([0, 1, 0])
    angulo = angulo_entre_vectores(v1, v2)
    print(f"(d) Ángulo entre vectores: {angulo:.2f}°")
    graficar_vectores_3d([v1, v2], "Vectores en 3D")

    # (e) 
    v1 = np.array([1, 0, 0])
    v2 = np.array([0, 1, 0])
    area = area_paralelogramo(v1, v2)
    print(f"(e) Área del paralelogramo: {area:.2f}")