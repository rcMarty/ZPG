//
// Created by rc_marty on 29.9.23.
//

#include "engine.h"
#include "../resources/models/square.h"
#include "../resources/models/suzi_flat.h"
#include "../object/mesh.h"
#include "../object/renderable_object.h"
#include "stdio.h"
#include "stdlib.h"
#include "../render/scene.h"
#include <memory>
#include <vector>
#include "../shader/shader_handler.h"

static void error_callback(int error, const char *description) { fputs(description, stderr); }

void Engine::init()
{

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // this->window = std::make_shared<GLFWwindow>(glfwCreateWindow(600, 600, "oop ČVEREC", NULL, NULL), glfwDestroyWindow);
    this->window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(1000, 1000, "oop ČVEREC", NULL, NULL), glfwDestroyWindow);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);

    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
    glfwGetFramebufferSize(window.get(), &width, &height);
    glViewport(0, 0, width, height);
}

void Engine::run()
{
    //todo scene

//    Shader_handler shaders;
//    shaders.add_shader(Shader_wrapper("../shader/vertex_shader/flat.vert","../shader/fragment_shader/flat.frag","flat4x4_point"))
//            .add_shader(Shader_wrapper("../shader/vertex_shader/flat_v3.vert","../shader/fragment_shader/flat_v3.frag","flat3x3"));

    Scene scene;
    scene.init();


    while (!glfwWindowShouldClose(window.get()))
    {
        //todo scene

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.render();
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window.get());
    }
}

void Engine::destroy() {
    glfwDestroyWindow(window.get());
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
