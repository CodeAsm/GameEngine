#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tiny_obj_loader.h>
#include <iostream>
#include <cstddef>

// Schermgrootte
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Functieprototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Verplaatsbare verlichting
float lightPosX = 1.2f, lightPosY = 1.0f, lightPosZ = 2.0f;

// Rotatiehoeken
float rotationX = 0.0f, rotationY = 0.0f;

int main()
{
    // Initialiseren van GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // OpenGL versie 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Maken van een venster
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Object Viewer", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD initialiseren
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Viewport instellen
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Lader voor OBJ-bestanden
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    // Laad het object
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "cube.obj"))
    {
        std::cerr << warn << err << std::endl;
        return -1;
    }

    // Hier komt de rest van je render logica

    while (!glfwWindowShouldClose(window))
    {
        // Invoer verwerken
        processInput(window);

        // Render logica hier

        // Buffers wisselen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotationX += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotationX -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotationY += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotationY -= 0.01f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        lightPosY += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        lightPosY -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        lightPosX -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        lightPosX += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        lightPosZ -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        lightPosZ += 0.01f;
}
