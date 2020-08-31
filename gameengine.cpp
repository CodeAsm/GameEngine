
#include "iostream"
#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
//#define DBG_Render    // Noisy
using namespace std;
// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(0.75f, 0.94f, 0.08f, 0.8f);\n"
    "}\n\0";
 

// Window dimensions (TODO: make configurable)
const GLuint WIDTH = 800, HEIGHT = 600;

#ifndef VERSION
#define VERSION "1.1"//; //TODO: this isnt working if we forget to define version.
#endif

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    //When user presses the Esc key, we set WindowShouldClose
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
        printf("[Kbd] Esc detected\n");
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) printf("[Kbd] W \n");
    if (key == GLFW_KEY_A && action == GLFW_PRESS) printf("[Kbd] A \n");
    if (key == GLFW_KEY_S && action == GLFW_PRESS) printf("[Kbd] S \n");
    if (key == GLFW_KEY_D && action == GLFW_PRESS) printf("[Kbd] D \n");
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) printf("[Kbd] Q \n");
    if (key == GLFW_KEY_E && action == GLFW_PRESS) printf("[Kbd] E \n");
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) printf("[Kbd] UP \n");
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) printf("[Kbd] LEFT \n");
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) printf("[Kbd] RIGHT \n");
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) printf("[Kbd] DOWN \n");
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) printf("[Kbd] SPACE \n");
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) printf("[Kbd] TAB \n");
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) printf("[Kbd] ENTER \n");
    
    
}

int main(int argc, char **argv)
{
    printf("Version: %s\n", VERSION);
    printf("[APP] Starting ...\n");

    // We setup the rendering statemachine and engine here
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    printf("[OpenGL] Making window\n");
    std::string title = "OpenGL \"Game\" Engine: ";
    GLFWwindow*window = glfwCreateWindow(WIDTH, HEIGHT,(title += VERSION).c_str(), nullptr,nullptr);
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
        -0.6f, -0.6f, 0.0f, // Left
        0.6f,  -0.6f, 0.0f, // Right
        0.0f,   0.6f, 0.0f  // Top
    };

    //Shaders be here
    //--------------------------------------------------------------------------
    // Build and compile our shader program
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("[ERR] SHADER:VERTEX COMPILATION_FAILED\n");//+  infoLog + "\n");
    }
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

        printf("[ERR] SHADER:FRAGMENT COMPILATION_FAILED\n");//+  infoLog + "\n");
    }
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("[ERR] SHADER:PROGRAM COMPILATION_FAILED\n");//+  infoLog + "\n");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    //--------------------------------------------------------------------------
    // End of shader stuff


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
        //Drawing actual stuff

        // Draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        // Done drawing
        
        //Swap buffers
        glfwSwapBuffers(window);

    }

    // Proper closing 
    printf("[OpenGL] Stopping ...\n");
    glfwTerminate();
    printf("[APP] Stopping ...\n");
    return 0;
}