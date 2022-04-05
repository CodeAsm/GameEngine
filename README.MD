# Gameengine

test game engine project, not much to see here yet

GLFW
GLEW

## Test if wich I like
- Phong Shading     no specular highlight difficulty of Gouraud shading.
- Blinn-Phong
- Gouraud Shading   interpolation technique for surface shading 
- Flat Shading

# Compiling
If you havent cloned yet:
```
git clone --recurse-submodules https://github.com/CodeAsm/GameEngine
```
else try:
Yadajada doodlely doodoo, only Linux, you need to:
```
git submodule init
git submodule update
```
before any
```
make
```
for cleaning (and no submodule is needed for this):
```
make clean
```

# Ideas
* Object loading
* Camera movement
* File altering
* Threading
* Object management


# Resources
## General Dev
<https://stackoverflow.com/questions/1950926/create-directories-using-make-file>

## Helpfull 3d
<http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/>
Used for my fakeFPS counter, more accurate.

<https://stackoverflow.com/questions/10535950/forcing-nvidia-gpu-programmatically-in-optimus-laptops/14041061#14041061>
Not implemented yet, but seems important
## 3d
<https://qiita.com/ssaattwworg/items/32ee9a6fdb0476833c02>
<https://github.com/gwerners/BasicGLFWImgui>
<https://blog.conan.io/2019/06/26/An-introduction-to-the-Dear-ImGui-library.html>

## Database
<https://github.com/jminor/sql-gui>

## Other helpfull
<https://stackoverflow.com/questions/14386856/c-check-currently-available-free-ram/57659190#57659190>
For memory info (and maybe more)
