# Tarea1.py 
## Librerías usadas
- numpy
- matplotlib.pyplot
- mpl_toolkits.mplot3d
## Primera función
```python
def polar_a_cartesianas(magnitud, direccion):
    direccion_rad = np.radians(direccion)  # Convierte grados a radianes
    x = magnitud * np.cos(direccion_rad)   # Calcula componente x
    y = magnitud * np.sin(direccion_rad)   # Calcula componente y
    return x, y
```
## Segunda función
```python
def cartesianas_a_polar(x, y):
    magnitud = np.sqrt(x**2 + y**2)               # Calcula la norma del vector
    direccion = np.degrees(np.arctan2(y, x))      # Ángulo en grados (-180° a 180°)
    return magnitud, direccion
```
## Tercera función
```python
def suma_vectores(magnitudes, direcciones):
    x_total, y_total = 0, 0
    for mag, dir in zip(magnitudes, direcciones):
        x, y = polar_a_cartesianas(mag, dir)      # Convierte cada vector a cartesianas
        x_total += x                              # Suma componentes x
        y_total += y                              # Suma componentes y
    magnitud_res, direccion_res = cartesianas_a_polar(x_total, y_total)
    return x_total, y_total, magnitud_res, direccion_res
```
## Cuarta función
```python
def angulo_entre_vectores(v1, v2):
    dot_product = np.dot(v1, v2)                  # Producto punto
    norm_v1 = np.linalg.norm(v1)                  # Norma del vector 1
    norm_v2 = np.linalg.norm(v2)                  # Norma del vector 2
    cos_theta = dot_product / (norm_v1 * norm_v2)  # Coseno del ángulo
    return np.degrees(np.arccos(cos_theta))       # retornamos el resultado convirtiéndolo a grados
```
## Quinta función
```python
def area_paralelogramo(v1, v2):
    cross_product = np.cross(v1, v2)               # Producto cruz
    return np.linalg.norm(cross_product)           # Norma del producto cruz = área
```

