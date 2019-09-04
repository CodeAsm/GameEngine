
#include "iostream"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
//#define DBG_Render    // Noisy

// Window dimensions (TODO: make configurable)
const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    //When user presses the Esc key, we set WindowShouldClose
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
        printf("[Kbd] Esc detected\n");
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS){
        printf("[Kbd] W \n");
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        printf("[Kbd] A \n");
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS){
        printf("[Kbd] S \n");
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS){
        printf("[Kbd] D \n");
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        printf("[Kbd] UP \n");
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        printf("[Kbd] LEFT \n");
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        printf("[Kbd] RIGHT \n");
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        printf("[Kbd] DOWN \n");
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        printf("[Kbd] SPACE \n");
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
    GLFWwindow*window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL \"Game\"Engine PreAlpha", nullptr,nullptr);
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
    glViewport(0,0,WIDTH,HEIGHT);    //The actual rendering image into the window (this can be smaller)

    //register keypres detection
    glfwSetKeyCallback(window,key_callback);


    //Test triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f,  -0.5f, 0.0f, // Right
        0.0f,   0.5f, 0.0f  // Top
    };

    //Shaders be here

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