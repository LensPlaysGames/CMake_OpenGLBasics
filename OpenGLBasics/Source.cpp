/*
* TODO:
*   - Placing objects at runtime (Simple example: Press space to place cube at camera position).
*   - InstancedObject abstraction for something that will be drawn a lot of times (will have a model, list of transform struct with positions, rotations, scales))
*   - Update lighting system (renderer + shader) to work with multiple lights, multiple types of lights
*   - Swap Blinn-Phong shading for PBR lighting (metallic, roughness, etc)
*   - Define more primitives: sphere, capsule, cylinder, torus
*   - Fix movement speed and sensitivity changing based on frame-rate
*   - Add cubemap skybox functionality
*   - Abstract Transform struct
*   - Better printf formatting (tabulate or another external header?)
*   - Update camera inputs from conditional to event-based
*   - Abstract object map to it's own class with functions to add and remove objects, etc
*   - Add colinear check to GetNormal() 
*   - Implement load timer for timing how long it takes to load models
*   - Make object creation asynchronous (so objects are rendered as they are added to the object map vs brick the program until all of them are)
*   - Make it possible to render to specific window.
*   - Add texture ability
*/

/*
* WELCOME! WELCOME! WELCOME!
* README :)
* 
* CONTROLS:
*   - W     Move Forward
*   - A     Move Left
*   - S     Move Backward
*   - D     Move Right
*   - Q     Move Up
*   - E     Move Down
* 
* In CreateObjects(), find out how to:
*   - Create and place an Object within the program:
*   - Load your own 3d models from file (.stl, .obj, .blend, and a lot more),
*   - Load and use your own shaders from file (written in GLSL):
*/ 


/* Render Pipeline Outline:
*   A Scene has a map<Shader*, vector<Object>> Objects that are drawn every frame using the given shader.
*   A Scene has a LightObject —a class holding a light, an object, and a shader— that will be drawn every frame and it's data used for lighting calculations.
*   A Scene has a Camera MainCamera that has transformation matrices used to calculate where on the screen to draw what.
*/

/* Proposed Render Pipeline Upgrades:
*   INSTANCING: 
*       A Scene has a map<Shader*, vector<InstancedObject>> InstancedObjects that are drawn instanced every frame using the given shader.
* 
*   MULTIPLE LIGHTS:
*       STEP 1:
*           A Scene has a vector<LightObject> that are drawn every frame and used for lighting calculations.
*       STEP 2:
*           A Scene has a LightObject DirectionalLight used for base lighting
*           A Scene has a vector<LightObject> PointLights used for point lighting
*           A Scene has a vector<LightObject> SpotLights used for spot lighting
*/

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

#include "Timer.h"
#include "Renderer.h"
#include "Primitives.h"
#include "FPSTimer.h"

#include <glm/gtc/matrix_transform.hpp>

/* I supposedly am responsible to `delete` everything that I create with `new`
*   I do that a lot...
* 
*   Occurences Found:
*       - Shaders       in CreateShader()
*       - Materials     in CreateObjects()
*       - Objects       in CreateObjects()
*/

/* WINDOW OPTIONS AND CONFIGURATION */
const static std::string WINDOW_TITLE = "OpenGL with GLFW + GLEW";          // SPECIFY TITLE OF WINDOW IN OS
const int START_MAXIMIZED = GLFW_TRUE;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

/* DIRECTORY STRUCTURE */

// Shaders in this directory can be compiled at runtime and used to render created objects in CreateObjects()
const static std::string SHADER_DIR = "../shaders/";                        // SPECIFY DIRECTORY TO FIND SHADERS IN
const static std::string DEFAULT_SHADER_VERTEX = "vertex.glsl";             // SPECIFY DEFAULT GLOBAL VERTEX SHADER HERE (POSITION, SHAPE)
const static std::string DEFAULT_SHADER_FRAGMENT = "fragment.glsl";         // SPECIFY DEFAULT GLOBAL FRAGMENT SHADER HERE (COLOR)

// Models can be loaded from file in CreateObjects()
const static std::string MODELS_DIR = "../models/";                         // SPECIFY DIRECTORY TO FIND 3D MODELS IN

/* Scene to be rendered by Renderer */
Scene g_Scene(
    Camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f)), 
    new LightObject());

#pragma region Math Helpers
static glm::quat QuaternionFromEuler(double eulerX, double eulerY, double eulerZ) {
    return glm::quat(glm::vec3(glm::radians(eulerX), glm::radians(eulerY), glm::radians(eulerZ)));
}

static glm::quat QuaternionFromEuler(int eulerX, int eulerY, int eulerZ) {
    return QuaternionFromEuler((double)eulerX, (double)eulerY, (double)eulerZ);
}

static float Lerp(float a, float b, float t) { return ((1 - t) * a + (t * b)) / 1.0f; }

static glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float t) { return glm::vec3(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t)); }
#pragma endregion

#pragma region GLFW
void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Randomize light color if 'Space' is pressed.
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glm::vec3 newColor = (glm::vec3((rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f));
        newColor = Lerp(g_Scene.MainLight->ObjLight->color, newColor, 1.0f);
        g_Scene.MainLight->SetColor(newColor);
    }
    // Set light color to white if 'C' is pressed.
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        g_Scene.MainLight->SetColor(glm::vec3(1.0f));
    }
}

void Exit(const char* msg) {
    printf("Application quitting: %s\n", msg);
    glfwTerminate();
}

void Exit() {
    /* Default exit message */
    Exit("Goodbye :)");
}

void glfwErrorCallback(int i, const char* err_str) {
    printf("ERROR::GLFW::%s\n", err_str);
}

void OnFramebufferSizeChangedCallback(GLFWwindow* window, int widthInPixels, int heightInPixels) {
    glViewport(0, 0, widthInPixels, heightInPixels);
}

void OnWindowSizeChangedCallback(GLFWwindow* window, int widthInScreenCoords, int heightInScreenCoords) {
    g_Scene.MainCamera.UpdateScreenSize(widthInScreenCoords, heightInScreenCoords);
}

GLFWwindow* InitializeWindow() {
    /* Print any errors GLFW throws to console */
    glfwSetErrorCallback(glfwErrorCallback);

    /* Initialize the GLFW library */
    if (!glfwInit()) {

        Exit("Failed to initialize GLFW!");
        return NULL;
    }

    glfwWindowHint(GLFW_MAXIMIZED, START_MAXIMIZED);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
    if (!window)
    {
        Exit("Failed to create GLFW window!");
        return NULL;
    }

    glfwMakeContextCurrent(window);

    /* Initialize the GLEW library */
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW failed to initialize. Error: %s\n", glewGetErrorString(err));
        Exit("Failed to initialize GLEW!");
        return NULL;
    }

    /* Attach callback to window resize to allow camera to update */
    glfwSetWindowSizeCallback(window, OnWindowSizeChangedCallback);

    /* Attach callback to framebuffer resize to allow viewport to update */
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChangedCallback);

    /* Attach callback to keypress to catch any user input that might need to be handled */
    glfwSetKeyCallback(window, OnKeyPressed);

    return window;
}
#pragma endregion

#pragma region Object Creation Helpers
/* OBJECT CREATION HELPER METHODS*/

/* Create model from file name */
Model CreateModel(const char* fileName) { return Model((MODELS_DIR + fileName).c_str()); }

/* Create shader (load source, compile, link) from file names */
Shader* CreateShader(const char* vertexFilename, const char* fragmentFilename) { return new Shader((SHADER_DIR + vertexFilename).c_str(), (SHADER_DIR + fragmentFilename).c_str()); }
#pragma endregion

void CreateObjects() {
    // Basic idea: create a Model, then use a Shader and that Model to create an object in the map.
    // All objects in the global object map will be rendered each frame in the main loop using shader.

    /* SHADER CREATION
    *   Create Shader from files in SHADER_DIR using the following syntax:
    *       Preferred (from SHADER_DIR):    'Shader* {Shader Name} = CreateShader({Vertex Shader File Name}.c_str(), {Fragment Shader File Name}.c_str());'
    *       From custom directory:          'Shader* {Shader Name} = new Shader(({Shader Directory} + {Vertex Shader File Name}).c_str(), ({Shader Directory} + {Vertex Shader File Name}).c_str());'
    */
    Shader* defaultShader = CreateShader(DEFAULT_SHADER_VERTEX.c_str(), DEFAULT_SHADER_FRAGMENT.c_str());
    Shader* solid = CreateShader(DEFAULT_SHADER_VERTEX.c_str(), "fragment_solid.glsl");
    Shader* lit = CreateShader(DEFAULT_SHADER_VERTEX.c_str(), "fragment_lit.glsl");

    glUseProgram(defaultShader->ID);

    /* MATERIAL CREATION 
    *   A Material defines properties that influence how a Model will look in the Scene.
    *   Namely, the color and the lighting properties.
    * 
    *   MATERIAL PROPERTIES (TYPE, NAME - DESCRIPTION):
    *       - glm::vec3 color       - The base color of the object to be affected by lighting.
    *       - glm::vec3 ambient     - Influences color of ambient light (keep low values).
    *       - glm::vec3 diffuse     - Multiplied by light ambient color to get final ambient value.
    *       - glm::vec3 specular    - Influences lighting highlight color.
    *       - float shininess       - Influences lighting highlight size and intensity (higher = less intense).
    * 
    *   Create a pointer to a Material using the following syntax(es):
    *       Default:                'new Material()'
    *       From Color:             'Material* {Material Name} = new Material()({Color})'
    *       From Color + Lighting:  'Material* {Material Name} = new Material()({Color}, {Ambient}, {Diffuse}, {Specular}, {Shininess})'
    *       Copy Another Material:  'Material* {Material Name} = new Material({Pointer to Material To Copy});
    *       Copy Material Except Color
    */

    // Colorful Materials!
    Material* MAT_grey = new Material(glm::vec3(0.666f));
    Material* MAT_red = new Material(glm::vec3(1.0f, 0.0f, 0.0f));
    Material* MAT_green = new Material(glm::vec3(0.0f, 1.0f, 0.0f));
    Material* MAT_blue = new Material(glm::vec3(0.0f, 0.0f, 1.0f));
    
    // Absorbative Materials (dark ambient, diffuse, and specular).
    Material* MAT_absorbative = new Material(glm::vec3(0.75f), glm::vec3(0.05f), glm::vec3(0.56f), glm::vec3(0.12f), 16.0f);
    Material* MAT_absorbativeRed = new Material(MAT_absorbative);
    MAT_absorbativeRed->color = glm::vec3(MAT_absorbativeRed->color.r, 0.0f, 0.0f);
    Material* MAT_absorbativeGreen = new Material(MAT_absorbative);
    MAT_absorbativeGreen->color = glm::vec3(0.0f, MAT_absorbativeGreen->color.g, 0.0f);
    Material* MAT_absorbativeBlue = new Material(MAT_absorbative);
    MAT_absorbativeBlue->color = glm::vec3(0.0f, 0.0f, MAT_absorbativeBlue->color.b);

    /* MODEL CREATION
    *   Create a 3D-Model using the following syntax(es):
    *       From Mesh:          'Model {Model Name}({Mesh})'
    *       From vector<Mesh>:  'Model {Model Name}({Meshes})'
    *       From File:          'Model {Model Name} = CreateModel({File Name});'
    */

    // 3D Primitives
    Model cube = Primitives::Cube();
    Model pyramid = Primitives::Pyramid();

    // 2D Primitives
    Model triangle = Primitives::Triangle();
    Model square = Primitives::Square();

    // Loaded from file
    Model motopig = CreateModel("MotoPig.stl");
    Model benchy = CreateModel("3DBenchy.3mf");
    Model sloth = CreateModel("sloth.obj");
    Model astronaut = CreateModel("astronaut.stl");

    /* OBJECT CREATION 
    *   An Object is rendered every frame if it is within the global Scene Objects map (or if additional code is added to render it in the main loop).
    *   
    *   OBJECT PROPERTIES (TYPE, NAME - DESCRIPTION):
    *       - Model ObjModel            - The 3D-Model to draw each frame. If none is provided, the object is not drawn.
    *       - glm::vec3 Position        - The location of the model in world coordinates. All the vertices of the model will be offset by this number when drawn.
    *       - glm::quat Rotation        - The orientation of the model in Quaternion form. Helper functions: QuaternionFromEuler(angleX, angleY, angleZ)
    *       - glm::vec3 Scale           - The size of the model; a multiplier, so default is 1.
    * 
    *   Create an Object with Shader, Model, *Position, *Rotation, and *Scale with the following syntax(es):
    *       From Model:     'g_Objects[{Shader Ptr}].push_back(new Object({Model}, {*Position}, {*Rotation}, {*Scale}));'
    *       From Object:    'g_Objects[{Shader Ptr}].push_back({Object Ptr});'
    *   '*' = optional (to an extent, cpp doesn't allow multiple overloads differentiated just by name, must be by type, so only certain combinations are available).
    */

    /* Place objects along all axes at Highlight offset from every Stride-th position.*/
    const int EdgeCount = 34;   // How many cubes in each direction?
    const int Stride = 6;       // How many units to skip between placing cubes?
    const int Highlight = 0;    // Offset within stride.
    for (int z = 1; z < EdgeCount + 1; z++)
    {
        for (int y = 1; y < EdgeCount + 1; y++)
        {
            for (int x = 1; x < EdgeCount + 1; x++)
            {
                if (x % Stride == (Highlight % Stride) && y % Stride == (Highlight % Stride) && z % Stride == (Highlight % Stride)) {
                    glm::quat rotation = QuaternionFromEuler(rand() % 360, rand() % 360, rand() % 360);
                    g_Scene.Objects[lit].push_back(new Object(cube, glm::vec3(x, y, -z), rotation));
                    g_Scene.Objects[lit].push_back(new Object(pyramid, glm::vec3(-x, y, -z), rotation));
                }
            }
        }
    }

    /* UNLIT */
    //g_Scene.Objects[defaultShader].push_back(new Object(cube, glm::vec3(0.0f, -2.0f, 0.0f)));
    //g_Scene.Objects[defaultShader].push_back(new Object(cube, glm::vec3(2.0f, 0.0f, 0.0f), QuaternionFromEuler(0, 30, 0)));

    //g_Scene.Objects[defaultShader].push_back(new Object(triangle, glm::vec3(0.0f, -4.0f, 0.0f)));
    //g_Scene.Objects[defaultShader].push_back(new Object(square, glm::vec3(0.0f, -5.0f, 0.0f)));

    //g_Scene.Objects[defaultShader].push_back(new Object(motopig, glm::vec3(-5.0f, 2.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));

    //g_Scene.Objects[solid].push_back(new Object(triangle, glm::vec3(-1.0f, -4.0f, 0.0f)));
    //g_Scene.Objects[solid].push_back(new Object(square, glm::vec3(-1.0f, -5.0f, 0.0f)));

    //g_Scene.Objects[solid].push_back(new Object(motopig, glm::vec3(0.0f, 2.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));

    /* LIT */
    g_Scene.Objects[lit].push_back(new Object(cube));

    /* Cyan triangle atop a grey square */
    triangle.SetMaterial(new Material(glm::vec3(0.01f, 1.0f, 1.0f)));
    g_Scene.Objects[lit].push_back(new Object(triangle, glm::vec3(-2.0f, -4.0f, 0.0f)));
    g_Scene.Objects[lit].push_back(new Object(square, glm::vec3(-2.0f, -5.0f, 0.0f)));

    /* Test models loaded from file */
    g_Scene.Objects[lit].push_back(new Object(sloth, glm::vec3(-250.0f, 0.0f, -175.0f), QuaternionFromEuler(55, 0, 90), glm::vec3(5.0f)));
    g_Scene.Objects[lit].push_back(new Object(benchy, glm::vec3(-10.0f, 0.0f, 2.0f), QuaternionFromEuler(-90, -90, 0), glm::vec3(0.075f)));
    g_Scene.Objects[lit].push_back(new Object(sloth, glm::vec3(-15.0f, 0.0f, 0.0f), QuaternionFromEuler(0, 0, 90), glm::vec3(0.1f)));

    /* Colorful motopig array */
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(5.0f, 2.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_grey);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(9.0f, 2.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_absorbative);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(13.0f, 2.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_absorbativeRed);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(5.0f, 6.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_absorbativeGreen);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(9.0f, 6.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_absorbativeBlue);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(13.0f, 6.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_red);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(5.0f, 10.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_green);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(9.0f, 10.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));
    motopig.SetMaterial(MAT_blue);
    g_Scene.Objects[lit].push_back(new Object(motopig, glm::vec3(13.0f, 10.0f, 2.0f), QuaternionFromEuler(0, 90, 90), glm::vec3(0.2f)));

    /* He looks awfully lonely out there... */
    g_Scene.Objects[lit].push_back(new Object(astronaut, glm::vec3(-2.0f, 6.0f, 4.2f), QuaternionFromEuler(-90, 0, 0), glm::vec3(0.05f)));

    /* Light configuration */
    glm::vec3 lightColor(1.0f);
    // Create and set Object Material.
    g_Scene.MainLight->Obj->ObjModel.SetMaterial(new Material(lightColor));
    // Set Light color to the same color as Material.
    g_Scene.MainLight->ObjLight->color = lightColor;
    // Create an Object at the Light's current position and assign it to the Main Light's Object.
    g_Scene.MainLight->Obj = new Object(cube, g_Scene.MainLight->ObjLight->position, glm::vec3(0.25f));
    // Use solid shading.
    g_Scene.MainLight->ObjShader = solid;
}

const double FPSInTitleUpdatesPerSecond = 2.0;
void FpsTitleTimer(GLFWwindow* window) {
    FPSTimer::AddFrame(Timer::deltaTime);
    if (Timer::time - FPSTimer::lastTimeFPSUpdated >= 1.0 / FPSInTitleUpdatesPerSecond) {
        FPSTimer::UpdateValues(Timer::time);
        glfwSetWindowTitle(window, (WINDOW_TITLE + " | " + std::to_string(FPSTimer::frameTimeInMilliseconds) + "ms" + " | " + std::to_string(FPSTimer::FPS) + "fps").c_str());
    }
}

int main(void)
{
    GLFWwindow* window = InitializeWindow();

    /* Print version number to console */
    printf("OpenGL Version %s\n", glGetString(GL_VERSION));

    /* Object creation - Populate global scene objectMap with objects 
    *   Add and/or change this function to change the scene arrangement!
    */
    CreateObjects();

    // Enable OpenGL features that are disabled by default.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_STENCIL_TEST);

    Renderer renderer;

    // Configure light
    glm::vec3 initialLightPosition(0.0f, 10.0f, 10.0f);
    g_Scene.MainLight->MoveLight(initialLightPosition);

    /* Loop until the window should close */
    while (!glfwWindowShouldClose(window))
    {
        /* TIME */
        Timer::Update(glfwGetTime());

        /* CAMERA */
        g_Scene.MainCamera.Update(window);

        /* SCENE MANIPULATION */

        // Move light
        glm::vec3 mainLightPositionOffset(0.0f);

        /* Move light in XZ-axis circle over time */
        float radius = 2.0f;
        float speed = 1.0f;
        float scaleX = 10.0f;
        float scaleZ = 1.0f;
        mainLightPositionOffset = glm::vec3(scaleX * radius * sin(Timer::time * speed), 0.0f, scaleZ * radius * cos(Timer::time * speed));

        g_Scene.MainLight->MoveLight(initialLightPosition + mainLightPositionOffset);

        /* RENDERING */
        renderer.DrawScene(g_Scene);
        /* Swap front and back buffers. 
        *   Screen is showing front buffer while the back buffer is being rendered to.
        *   Number of buffers can be increased with the downside of increased input latency.
        */
        glfwSwapBuffers(window);        

        /* FPS and Frame Time in ms in Window Title */
        FpsTitleTimer(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Set previous frame time to current frame time for next frame */
        Timer::previousTime = Timer::time;
    }

    for (auto& i : g_Scene.Objects) {
        Shader* shader = i.first;
        for(auto& object : i.second)
        {
            delete object;
        }   
        delete shader;
    }

#pragma region Print End Statistics
    int width = 0;
    int height = 0;
    int* width_ptr = &width;
    int* height_ptr = &height;
    glfwGetWindowSize(window, width_ptr, height_ptr);
    int numberOfPixels = width * height;

    const std::string closeMSG = "Statistics on Application Close:\n";
    std::string pixelsPerSecond = std::to_string(FPSTimer::FPS * numberOfPixels);
    int n = pixelsPerSecond.length() - 3;
    while (n > 0) {
        pixelsPerSecond.insert(n, ",");
        n -= 3;
    }
    printf(("\n"
           + closeMSG
           + "    AVG FPS: " + std::to_string(FPSTimer::FPS) + "fps\n"
           + "    AVG FRAME TIME: " + std::to_string(FPSTimer::frameTimeInMilliseconds) + "ms\n"
           + "    AVG PIXELS PROCESSED PER SECOND: " + pixelsPerSecond + " pixels\n"
           + "\n").c_str());
#pragma endregion

    glfwDestroyWindow(window);

    Exit();
    return 0;
}