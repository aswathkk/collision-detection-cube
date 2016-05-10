# collision-detection-cube
Simple collision detection sample in OpenGL 

# Building
Header file location may varry with respect to the installation. So fix the header file location first.
eg: in macOS, you have to use `#include <GLUT/glut.h>`. In linux, you need to use `#include <GL/glut.h>`.
Compiling in MacOS :
    $ g++ collision.c -framework OpenGL -framework GLUT -o collision
To run, 
    ./collision
Compiling in Linux :
    $ g++ collision.c -lGL -lGLU -lglut -o collision

# Controls
Cube 1
w -> up
s -> down
a -> left
d -> right

Cube 2
i -> up
k -> down
j -> left
l -> right
