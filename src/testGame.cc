#include "testGame.hh"
#include "displayManager.hh"
#include "gameTime.hh"
#include "shader.hh"
#include "strRawShaders.hh"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cdxg {

    TestGame::TestGame(int initialWidth, int initialHeight, std::string initialTitle):
        GameTemplate(initialWidth, initialHeight, initialTitle){}

    TestGame::~TestGame(){
        delete mpShader;
    }

    void TestGame::Initialize(){
        // initialize Uinput
        glfwSetInputMode(DisplayManager::mpsWindow, GLFW_STICKY_KEYS, 0);

        //initialize GameTime
        GameTime::msDeltaTimeSec = 0.0f;
        GameTime::msTotalTimeSec = glfwGetTime();
        
        mpShader = new Shader(&RawShaders::source);

        unsigned int vao;
        unsigned int vbo;

        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        float vertices[] = {
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 1.0f, 1.0f
        };

        
    } // void Initialize()

    void TestGame::Update(){
        //update GameTime
        GameTime::msDeltaTimeSec = glfwGetTime() - GameTime::msTotalTimeSec;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Update()

    void TestGame::Render(){
        //blank screen w/ bg color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg