# Pixels of pain

smthng like path of pain but in opengl (its till pain)

## Description

This is my project to essentials of computer graphics course written in c++ and opengl. It is basically the simplest
render engine you can imagine.

Citation from my university:

> The aim of the course is to introduce students to the basics of computer graphics. To gain an overview of the basic
> principles of 2D and especially 3D computer graphics. During the semester, students will learn the basic principles of
> the graphics card and the display chain. The basic algorithms used in computer graphics will be presented step by
> step.
> The result will be a project on which students will demonstrate the knowledge they have gained, which will allow them
> to
> display a 3D scene, move the camera, objects, adjust lights, colors, textures, add shadows, transparency, normal maps,
> etc. to the scene.

## Table of Contents

- [Project Name](#pixels-of-pain)
- [Description](#description)
- [Table of Contents](#table-of-contents)
- [ToDo](#todo)
- [Demo](#demo)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## ToDo

- [ ] add delta time to camera movement and other objects
- [x] add textures
- [ ] add Debug class

## Demo

**_there will be link to another readme_**

## Installation

You must have installed these libraries:

```
glfw3 3.3
OpenGL
GLEW
glm
assimp
```

And then build it with cmake

```bash
mkdir build
cd build
cmake ..
make
./ZPG
```

## Usage

Run compiled program

Movement:

- W - forward
- S - backward
- A - left
- D - right
- Q - up
- E - down

Camera:

- Arrow up - rotate up
- Arrow down - rotate down
- Arrow left - rotate left
- Arrow right - rotate right

Other:

- SPACE - lock/unlock cursor
- Mouse when cursor is locked - look around
- B - (only debug scene) add one point into Bézier curve (one little rat on the ground)
- R - (only debug scene) plant a spinning rat on the object
