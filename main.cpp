//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "engine/engine.h"

int main() {
    Engine engine;
    engine.init();
    engine.run();
}

