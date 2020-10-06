#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "common.hpp"
#include "demos/demo.hpp"
#include "demos/triangleDemo.hpp"
#include "demos/boxesDemo.hpp"
#include "demos/normalMapDemo.hpp"
#include "demos/hdrBloomDemo.hpp"

static void glfw_mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Demo *demo = nullptr;

static void printDebugInfo()
{
    // Print graphics driver vendor and OpenGL information
    const GLubyte *renderer = glGetString( GL_RENDERER ); 
    const GLubyte *vendor = glGetString( GL_VENDOR ); 
    const GLubyte *version = glGetString( GL_VERSION ); 
    const GLubyte *glslVersion = 
        glGetString( GL_SHADING_LANGUAGE_VERSION ); 
    
    GLint major, minor; 
    glGetIntegerv(GL_MAJOR_VERSION, &major); 
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    
    printf("GL Vendor            : %s\n", vendor); 
    printf("GL Renderer          : %s\n", renderer); 
    printf("GL Version (string)  : %s\n", version); 
    printf("GL Version (integer) : %d.%d\n", major, minor); 
    printf("GLSL Version         : %s\n", glslVersion);

    // Extension information
    GLint nExtensions; 
    glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions); 
    
    for( int i = 0; i < nExtensions; i++ ) 
        printf("%s\n", glGetStringi( GL_EXTENSIONS, i ) );
}

void switchDemo(Demo *d, GLFWwindow* window)
{
    demo->Unload();
    delete demo;
    demo = d;
    demo->Init(window);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Note: GLSL version above 330 matches OpenGL 3.3+ version
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL3+GLFW+GLAD+GLM+ImGui example", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
    glfwSetCursorPosCallback(window, glfw_mouse_callback);
    glfwSetScrollCallback(window, glfw_scroll_callback);
    glfwSwapInterval(1); // Enable vsync

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize OpenGL loader
    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    stbi_set_flip_vertically_on_load(true);

    // Viewport
    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    int capture_input_key_prev = GLFW_RELEASE;
    int capture_input_key = GLFW_RELEASE;
    bool capture_input = true;

    // Our state
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    demo = new TriangleDemo();
    demo->Init(window);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        capture_input_key_prev = capture_input_key;
        capture_input_key  = glfwGetKey(window, GLFW_KEY_F);
        if(capture_input_key != capture_input_key_prev && capture_input_key == GLFW_RELEASE)
        {
            capture_input = !capture_input;
            if(capture_input)
            {
                firstMouse = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, glfw_mouse_callback);
                glfwSetScrollCallback(window, glfw_scroll_callback);
                io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetCursorPosCallback(window, NULL);
                glfwSetScrollCallback(window, NULL);
                io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // Init ImGui window
        {
            ImGui::Begin("Demo select");

            ImGui::Text("Press F to toggle input capture");

            ImGui::Checkbox("Demo Window", &show_demo_window);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            ImGui::Separator();

            if (ImGui::Button("Triangle Demo", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                switchDemo(new TriangleDemo(), window);

            if (ImGui::Button("Boxes Demo", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                switchDemo(new BoxesDemo(), window);

            if (ImGui::Button("Normal Map Demo", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                switchDemo(new NormalMapDemo(), window);

            if (ImGui::Button("HDR Bloom Demo", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                switchDemo(new HdrBloomDemo(), window);

            ImGui::Separator();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        if(capture_input)
            demo->processKeyboard(window);

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        demo->Draw(window);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    demo->Unload();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    delete demo;

    return 0;
}

static void glfw_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float offsetX = xpos - lastX;
    float offsetY = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    demo->processMouse(window, xpos, ypos, offsetX, offsetY);
}

static void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    demo->processScroll(window, xoffset, yoffset);
}