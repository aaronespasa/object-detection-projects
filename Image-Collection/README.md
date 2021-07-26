# Capturar las imágenes para el proyecto

|                      Webcam software                      |           Imágenes creadas en las carpetas            |
   | :----------------------------------------------------------: | :----------------------------------------------------------: |
   | <img src="https://github.com/aaronespasa/object-detection-projects/blob/main/Readme-Resources/webcam.png" style="zoom: 50%;" /> | <img src="https://github.com/aaronespasa/object-detection-projects/blob/main/Readme-Resources/images-folder.png" style="zoom: 50%;" /> |

## Preparación y requisitos

### Environment de anaconda
Como buena práctica, vamos a utilizar un environment con Anaconda.

[Click para instalar Anaconda](https://www.anaconda.com/products/individual)

Para crear un environment con el nombre `cv` utilizamos el siguiente comando:

`$ conda create --name cv`

Activa el environment `cv`:

`$ conda activate cv`

Ahora instala las librerías necesarias (se encuentran en el archivo `object-detection-projects/Image-Collection/requirements.txt`):

`$ conda install ./Image-Collection/requirements.txt`

### CMake y OpenCV para C++
Para ejecutar el código de la webcam utilizamos C++.

Por lo tanto, necesitamos instalar CMake y construir OpenCV para C++:

#### CMake
- MacOS: `brew install cmake`
- Ubuntu: `sudo apt-get -y install cmake`
- Windows: [Descargas de CMake](https://cmake.org/download/)

#### OpenCV para C++
Vuelve a la carpeta antes de entrar al repositorio clonado `$ cd ..`

Ahora descarga el último release de opencv:

[Releases de OpenCV](https://github.com/opencv/opencv/releases)

Debes descargar el `Source code (zip)` y desencriptarlo.

Accede desde terminal a la carpeta desencriptada de ese zip.

Crea una nueva carpeta `build` y accede a ella: `$ mkdir build && cd build`.

Construye OpenCV:

`$ cmake ../`

`$ make`

`$ sudo make install`

## Ejecutar el código
Considero que estás en terminal dentro de `/object-detection-projects` y con el environment `cv` activado.
### Image-Collection
Accede a esta carpeta ejecutando el comando `$ cd Image-Collection`

Crea la carpeta build: `$ mkdir build && cd build`

Ahora construye el proyecto: `$ cmake ../ && make`

Ya puedes salir de la carpeta build `$ cd ..`

Ya está todo listo para ejecutar el notebook de python! 🎉
