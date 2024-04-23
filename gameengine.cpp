/*===============================================

    Main Gameengine source file
    Copyright CodeAsm 2020-2024 Nico Vijlbrief

https://github.com/CodeAsm/GameEngine
=================================================*/
#include "iostream"
#include <string>

#include "lib/kine/segment.cpp"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// SDL2
#include "SDL.h"
#include "SDL_mixer.h"
//#define DBG_Render    // Noisy
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
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
const GLuint WIDTH = 1024, HEIGHT = 720;

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

    const char* glsl_version = "#version 330 core";
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



    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

 //   glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

    //--------------------------------------------------------------------------
    // End of shader stuff

    printf("[Game] setting up imgui\n");
     // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 0.8;
    //style.WindowFillAlphaDefault = 0.83;
    //style.ChildWindowRounding = 3;
    style.WindowRounding = 3;
    style.GrabRounding = 1;
    style.GrabMinSize = 20;
    style.FrameRounding = 3;


    style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    //style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    //style.Colors[ImGuiCol_ComboBg] = ImVec4(0.16f, 0.24f, 0.22f, 0.60f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    //style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 0.50f, 0.50f, 0.33f);
    //style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.00f, 0.50f, 0.50f, 0.47f);
    //style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    //style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.78f, 0.78f, 0.35f);
    //style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.78f, 0.78f, 0.47f);
    //style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.78f, 0.78f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
    //style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.00f, 0.13f, 0.13f, 0.90f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.04f, 0.10f, 0.09f, 0.51f);




    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;
    float spf = 0;
    bool show = 0;


    Vector2D vec1(0.0, .0, 0.0, 100.0);
    vec1.Name = L"A";

    printf("[Game] entering game-loop\n");
    /// The big game loop
    while (!glfwWindowShouldClose(window))
    {

        //Check and call events
        glfwPollEvents();

        // Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
            spf = 1000.0/double(nbFrames);
			if(show)printf("%f ms/frame\n", spf);
			nbFrames = 0;
			lastTime += 1.0;
		}

       // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render your GUI
    ImGui::Begin("Demo window");
    if (ImGui::Button("Debug"))
    {
        show = !show;
    }

    if (show){  
        ImGui::Text("%f ms/frame\n", spf);
        ImGui::Text("Version: %s", VERSION);
        ImGui::Text("------------\n");
    }
    

    ImGui::Text("Segment: %S", vec1.Name.c_str());
    //ImGui::Text("MyObj num: %d", myObj.myNum);
    ImGui::Text("%S length=%.2f angle=%.2f",vec1.Name.c_str(),vec1.length(),vec1.getAngle());
    if (ImGui::Button("Decrease"))
    {
     //   myObj.myNum = myObj.myNum - 1;
            vec1.setAngle(vec1.getAngle() - 1);
    }
    ImGui::SameLine(75);
    if (ImGui::Button("Increase"))
    {
       //myObj.myNum = myObj.myNum + 1;
            vec1.setAngle(vec1.getAngle() + 1);
    }


    ImGui::End();


        //Rendering commands
        //clear previous thing 
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.035f, 0.137f, 0.219f, 1.0f); //Dark blue
    //    glClear(GL_COLOR_BUFFER_BIT);
#ifdef DBG_Render
        printf("[Renderer] Cleared buffer\n");
#endif
        //Drawing actual stuff

        //adjust for screen
        //WIDTH = 1024, HEIGHT = 720;
        // Draw a line
        ImGui::GetBackgroundDrawList()->AddLine(vec1.getp1(WIDTH,HEIGHT), vec1.getp2(WIDTH,HEIGHT), IM_COL32(255, 255, 255, 255), 2.0f);

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);


    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Swap buffers
        glfwSwapBuffers(window);

    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Proper closing
    printf("[OpenGL] Stopping ...\n");
    glfwTerminate();
    printf("[APP] Stopping ...\n");
    return 0;
}
