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

        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)(2*sizeof(vertices[0])));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Initialize shader
        mpShader->Load();
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

        mpShader->Use();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg