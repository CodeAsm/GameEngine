
#include "iostream"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
//#define DBG_Render    // Noisy

//Test triangle
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    //When user presses the Esc key, we set WindowShouldClose
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
        printf("[Kbd] Esc detected\n");
    }
}

int main(int argc, char **argv)
{

    printf("[APP] Starting ...\n");

    // We setup the rendering statemachine and engine here
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

    //register keypres detection
    glfwSetKeyCallback(window,key_callback);

    printf("[Game] entering game-loop\n");
    /// The big game loop
    while (!glfwWindowShouldClose(window))
    {
        //Check and call events
        glfwPollEvents();

        //Rendering commands
        //clear previous thing
        glClearColor(0.035f, 0.137f, 0.219f, 1.0f); //Dark blue
        glClear(GL_COLOR_BUFFER_BIT);
#ifdef DBG_Render
        printf("[Renderer] Cleared buffer\n");
#endif
        //Swap buffers
        glfwSwapBuffers(window);

    }

    // Proper closing 
    printf("[OpenGL] Stopping ...\n");
    glfwTerminate();
    printf("[APP] Stopping ...\n");
    return 0;
}