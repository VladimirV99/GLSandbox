#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

#include "common.hpp"
#include "demos/demo.hpp"
#include "demos/triangleDemo.hpp"
#include "demos/boxesDemo.hpp"
#include "demos/normalMapDemo.hpp"
#include "demos/hdrBloomDemo.hpp"

static void glfwMouseCallback(GLFWwindow* window, double xpos, double ypos);
static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

Demo *demo = nullptr;
bool captureInput = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

static void printDebugInfo()
{
    // Print graphics driver vendor and OpenGL information
    const char *renderer = (char *)glGetString( GL_RENDERER ); 
    const char *vendor = (char *)glGetString( GL_VENDOR ); 
    const char *version = (char *)glGetString( GL_VERSION ); 
    const char *glslVersion = 
        (char *)glGetString( GL_SHADING_LANGUAGE_VERSION ); 
    
    GLint major, minor; 
    glGetIntegerv(GL_MAJOR_VERSION, &major); 
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    
    spdlog::debug("GL Vendor            : {}", vendor); 
    spdlog::debug("GL Renderer          : {}", renderer); 
    spdlog::debug("GL Version (string)  : {}", version); 
    spdlog::debug("GL Version (integer) : {}.{}", major, minor); 
    spdlog::debug("GLSL Version         : {}", glslVersion);

    // Extension information
    GLint nExtensions; 
    glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions); 
    
    spdlog::debug("GL Extensions:");
    for( int i = 0; i < nExtensions; i++ ) 
        spdlog::debug("\t{}", (char *)glGetStringi( GL_EXTENSIONS, i ) );
}

void switchDemo(Demo *d, GLFWwindow* window)
{
    demo->Unload();
    delete demo;
    demo = d;
    demo->Init(window);
}

static void glfwErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    exit(EXIT_FAILURE);
}

static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int, char**)
{
    spdlog::set_level(spdlog::level::debug);

    // Setup window
    glfwSetErrorCallback(glfwErrorCallback);
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
    glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);
    glfwSetCursorPosCallback(window, glfwMouseCallback);
    glfwSetScrollCallback(window, glfwScrollCallback);
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
    // printDebugInfo();

    stbi_set_flip_vertically_on_load(true);

    // Viewport
    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
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

    bool captureInputKeyPressed = false;

    // Our state
    bool showDemoWindow = false;
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

        // Input handlers
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !captureInputKeyPressed)
        {
            captureInput = !captureInput;
            captureInputKeyPressed = true;
            if(captureInput)
            {
                firstMouse = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        {
            captureInputKeyPressed = false;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        // Init ImGui window
        {
            ImGui::Begin("Demo select");

            ImGui::Text("Press F to toggle input capture");

            ImGui::Checkbox("Demo Window", &showDemoWindow);
            ImGui::ColorEdit3("clear color", (float*)&clearColor);

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

            if(demo->DrawMenu())
                ImGui::Separator();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        if(captureInput)
            demo->ProcessKeyboard(window, deltaTime);

        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        demo->Draw(window, deltaTime);

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

static void glfwMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!captureInput)
        return;
    
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

    demo->ProcessMouse(window, xpos, ypos, offsetX, offsetY);
}

static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!captureInput)
        return;
    
    demo->ProcessScroll(window, xoffset, yoffset);
}