
#include "iostream"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

int main(int argc, char **argv)
{

    printf("[APP] Starting ...\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    printf("[OpenGL] Making window\n");
    GLFWwindow*window = glfwCreateWindow(800, 600, "OpenGL demo", nullptr,nullptr);
    if (window == nullptr){
        printf("[OpenGL] Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        printf("[GLEW] Init failed");
        return -1;
    }
    glViewport(0,0,800,600);    //The actual rendering image into the window (this can be smaller)

    printf("[Game] entering game-loop\n");
    /// The big game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    printf("[OpenGL] Stopping ...\n");
    glfwTerminate();
    printf("[APP] Stopping ...\n");
    return 0;
}