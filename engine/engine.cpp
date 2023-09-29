//
// Created by rc_marty on 29.9.23.
//

#include "engine.h"
#include "../shader/shader.h"

static void error_callback(int error, const char *description) { fputs(description, stderr); }

void engine::init()
{

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    // this->window = std::make_shared<GLFWwindow>(glfwCreateWindow(600, 600, "oop ČVEREC", NULL, NULL), glfwDestroyWindow);
    this->window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(600, 600, "oop ČVEREC", NULL, NULL), glfwDestroyWindow);

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

void engine::run()
{

    //todo create objects and loading
    // replace all this with objects

    struct point
    {
        float pos[4];
        float color[4];
    };

    const point b[] = {
            { { -.5f, -.5f, .5f, 1 }, { 1, 0, 0, 1 } },
            { { -.5f, .5f, .5f, 1 }, { 0, 1, 0, 1 } },
            { { .5f, .5f, .5f, 1 }, { 0, 0, 1, 1 } },
            { { .5f, -.5f, .5f, 1 }, { 1, 1, 1, 1 } },
    };




    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(b), b, GL_STATIC_DRAW);


    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)16);

    auto shader = Shader::create_shader("../shader/vertex_shader/flat.vert","../shader/fragment_shader/flat.frag");

    while (!glfwWindowShouldClose(window.get()))
    {

        //todo scene

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(VAO);
        // draw triangles
        glDrawArrays(GL_POLYGON, 0, 4); // mode,first,count
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window.get());
    }
}

void engine::destroy() {
    glfwDestroyWindow(window.get());
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
