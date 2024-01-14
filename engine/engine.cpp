//
// Created by rc_marty on 29.9.23.
//

#include "engine.h"
#include "../object/model/mesh.h"
#include "../object/renderable_object.h"
#include "stdio.h"
#include "stdlib.h"
#include "../render/scene.h"
#include "../input_handle/input_handler.h"
#include <memory>
#include <vector>
#include "time.h"

static void error_callback(int error, const char *description) { fputs(description, stderr); }

void Engine::init() {

    glfwSetErrorCallback(error_callback);


    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    //todo refactoring window and use

    // this->window = std::make_shared<GLFWwindow>(glfwCreateWindow(600, 600, "oop ČVEREC", NULL, NULL), glfwDestroyWindow);
    this->window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(1000, 1000, "PoS", NULL, NULL), glfwDestroyWindow);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(this->window.get(), input::key_callback);
    glfwSetMouseButtonCallback(this->window.get(), input::mouse_btn_callback);
    glfwSetCursorPosCallback(this->window.get(), input::cursor_callback);
    glfwSetWindowSizeCallback(this->window.get(), input::window_size_callback);

    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);

    // set input handler
    this->input_handler = std::make_shared<input::Input_handler>();
    glfwSetWindowUserPointer(window.get(), this->input_handler.get());

    // set callback for focusing and unfocusing mouse
    input_handler->subscribe([&](input::Key_event_data data) {
        static bool locked_cursor = false;
        if (data.key == GLFW_KEY_SPACE && data.action == GLFW_PRESS) {
            printf("[DEBUG] space pressed, lock_cursor = %d\n", locked_cursor);
            if (!locked_cursor) {
                glfwSetInputMode(this->window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                printf("[DEBUG] cursor locked\n");
                locked_cursor = true;
            } else {
                glfwSetInputMode(this->window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                printf("[DEBUG] cursor unlocked\n");
                locked_cursor = false;
            }
        }
    });


    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

    auto debug_scene = std::make_shared<Scene>(input_handler, window);
    debug_scene->set_debug_scene();
    this->scene.push_back(debug_scene);


    auto phong_scene = std::make_shared<Scene>(input_handler, window);
    phong_scene->set_phong_scene();
    this->scene.push_back(phong_scene);


    auto rotation_scene = std::make_shared<Scene>(input_handler, window);
    rotation_scene->set_rotation_scene();
    this->scene.push_back(rotation_scene);


    auto check_scene = std::make_shared<Scene>(input_handler, window);
    check_scene->set_check_phong_scene();
    this->scene.push_back(check_scene);


    for (auto &i: scene) {
        i->init();
    }
    //subscribe on tab switch scene
    input_handler->subscribe([&](input::Key_event_data data) {
        if (data.key == GLFW_KEY_TAB && data.action == GLFW_PRESS) {
            printf("[DEBUG] tab pressed\n");
            scene[current_scene]->set_inactive();
            current_scene = (current_scene + 1) % scene.size();
            scene[current_scene]->set_active();
        }
    });
    int MaxTextureImageUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxTextureImageUnits);
    printf("[DEBUG] Engine initialized and max texture units %d\n", MaxTextureImageUnits);

}

void Engine::run() {
    current_scene = 0;
    scene[current_scene]->set_active();


    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //printf("[DEBUG] FPS %f\n", fps);

        this->scene[current_scene]->render(1.0);

        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window.get());
    }
    destroy();
}

void Engine::destroy() {
    glfwDestroyWindow(window.get());
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
