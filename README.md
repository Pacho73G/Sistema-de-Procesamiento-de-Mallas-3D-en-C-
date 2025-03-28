# 🧊 Sistema de Procesamiento de Mallas 3D en C++

Este proyecto implementa un sistema interactivo por consola para manipular objetos 3D representados como mallas poligonales. El sistema permite cargar, gestionar y analizar estructuras tridimensionales compuestas por vértices, aristas y caras, ofreciendo funcionalidades clave como generación de cajas envolventes, búsquedas de vértices cercanos y rutas más cortas entre vértices.

---

## 🚀 Características principales

- 📦 Carga de mallas desde archivos `.txt` con estructura definida.
- 📋 Listado de objetos cargados y su información (vértices, aristas, caras).
- 🧱 Cálculo de cajas envolventes individuales y globales.
- 📍 Búsqueda de vértices más cercanos a un punto o a la envolvente.
- 📐 Cálculo de rutas más cortas entre vértices y hacia el centroide del objeto.
- 💾 Guardado y descarga de mallas desde/hacia archivo.
- 🖥️ Interfaz tipo consola con comandos tipo `$`.

---

## ⚙️ Estructura del proyecto

```bash
Proyecto/
├── main.cpp
├── Sistema.{h,cpp}       # Controlador principal del sistema
├── Malla.{h,cpp}         # Representación de la malla 3D
├── Vertice.{h,cpp}       # Estructura de vértices 3D
├── Arista.{h,cpp}        # Conexiones entre vértices
├── Cara.{h,cpp}          # Polígonos definidos por vértices
├── KdTree.{h,cpp}        # Árbol KD para búsqueda eficiente
├── Grafo.h               # Estructura para rutas más cortas
├── objeto.txt            # Ejemplo de archivo de malla
```

---

## 🧠 Estructuras y algoritmos destacados

- **Árbol KD** para búsqueda espacial eficiente de vecinos cercanos.
- **Centroide y caja envolvente** de objetos 3D.
- **Algoritmo de Dijkstra** para rutas más cortas en grafos.
- Gestión de múltiples objetos en memoria.
- Múltiples verificaciones de errores y mensajes interactivos.

---

## 🕹️ Comandos disponibles (modo consola)

- `cargar archivo.txt`
- `listado`
- `envolvente [nombre_objeto]`
- `v_cercano x y z [nombre_objeto]`
- `v_cercanos_caja nombre_objeto`
- `ruta_corta i1 i2 nombre_objeto`
- `ruta_corta_centro i nombre_objeto`
- `descargar nombre_objeto`
- `guardar nombre_objeto archivo.txt`
- `ayuda [comando]`
- `salir`

---

## 💡 Uso

Compila el proyecto con `g++`:

```bash
g++ *.cpp -o malla3D
./malla3D
```

> También puedes usar Dev C++, VS Code o cualquier IDE de tu preferencia.

---

## 📚 Créditos
Proyecto desarrollado como parte del curso de Estructura de Datos
Pontificia Universidad Javeriana – Facultad de Ingeniería

## 💻 Desarrollado por

**Francisco Guzmán**   
📧 franciscoguzmanv11@gmail.com  
🐙 [GitHub](https://github.com/Pacho73G)

---
