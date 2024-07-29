#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <tiny_obj_loader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

// Functie om shaderbroncode te lezen uit een bestand
std::string readShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error compiling shader: " << infoLog << std::endl;
    }

    return shader;
}

unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Error linking program: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

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

    // Shaders laden
    std::string vertexShaderSource = readShaderSource("vertex_shader.glsl");
    std::string fragmentShaderSource = readShaderSource("fragment_shader.glsl");

    // Shader programma creëren
    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

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

    // Vertex data verzamelen
    std::vector<float> vertices;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            float vx = attrib.vertices[3 * index.vertex_index + 0];
            float vy = attrib.vertices[3 * index.vertex_index + 1];
            float vz = attrib.vertices[3 * index.vertex_index + 2];
            vertices.push_back(vx);
            vertices.push_back(vy);
            vertices.push_back(vz);
        }
    }

    // Vertex data en buffers instellen
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);


    // Material properties
    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 32.0f);

    // Light properties
    glUniform3f(glGetUniformLocation(shaderProgram, "light.position"), lightPosX, lightPosY, lightPosZ);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.specular"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), 0.0f, 0.0f, 3.0f);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
    // Invoer verwerken
    processInput(window);

    // Render logica hier
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Gebruik het shader programma
    glUseProgram(shaderProgram);

    // Materiaal- en lichtinformatie bijwerken
    glUniform3f(glGetUniformLocation(shaderProgram, "light.position"), lightPosX, lightPosY, lightPosZ);

    // Model matrix met rotatie
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));

    // View matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Projection matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    // Uniform locaties verkrijgen
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

    // Stuur matrices naar shaders
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Tekenen van het object
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (6 * sizeof(float)));

    // Buffers wisselen
    glfwSwapBuffers(window);
    glfwPollEvents();
    }

    // Opruimen
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Escape key pressed." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        rotationX += 0.01f;
        std::cout << "Up key pressed. rotationX: " << rotationX << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        rotationX -= 0.01f;
        std::cout << "Down key pressed. rotationX: " << rotationX << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        rotationY += 0.01f;
        std::cout << "Left key pressed. rotationY: " << rotationY << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        rotationY -= 0.01f;
        std::cout << "Right key pressed. rotationY: " << rotationY << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        lightPosY += 0.01f;
        std::cout << "W key pressed. lightPosY: " << lightPosY << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        lightPosY -= 0.01f;
        std::cout << "S key pressed. lightPosY: " << lightPosY << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        lightPosX -= 0.01f;
        std::cout << "A key pressed. lightPosX: " << lightPosX << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        lightPosX += 0.01f;
        std::cout << "D key pressed. lightPosX: " << lightPosX << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        lightPosZ -= 0.01f;
        std::cout << "Q key pressed. lightPosZ: " << lightPosZ << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        lightPosZ += 0.01f;
        std::cout << "E key pressed. lightPosZ: " << lightPosZ << std::endl;
    }
}
