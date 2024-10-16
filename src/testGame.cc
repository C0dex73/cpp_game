#include "testGame.hh"
#include "displayManager.hh"
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <iostream>
#include "gameTime.hh"
#include "shader.hh"
#include "vertices.hh"
#include "displayable.hh"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cdxg{

    TestGame::TestGame(int initialWidth, int initialHeight, std::string initialTitle):
        GameTemplate(initialWidth, initialHeight, initialTitle)
        {}

    TestGame::~TestGame(){}

    void TestGame::Initialize(){
        // initialize Uinput
        glfwSetInputMode(DisplayManager::mpsWindow, GLFW_STICKY_KEYS, 0);

        static std::vector<VertexRGB> v = {
            VertexRGB(-0.2, -0.2, 1.0, 0.0, 0.0),
            VertexRGB(0.2, 0.2, 0.0, 1.0, 0.0),
            VertexRGB(-0.2, 0.2, 0.0, 0.0, 1.0),
            VertexRGB(0.2, -0.2, 1.0, 1.0, 1.0)
        };
        rectangle.setVertices(v, false);
        static std::vector<unsigned int> i = {
            0, 1, 2, 0, 1, 3
        };
        rectangle.setVerticesIndices(i, false);
        static Shader s = Shader(&RawShaders::rgb);
        rectangle.setShader(&s);
        rectangle.load();

        //initialize GameTime
        GameTime::msDeltaTimeSec = 0.0f;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Initialize()

    void TestGame::Update(){
        //update GameTime
        GameTime::msDeltaTimeSec = glfwGetTime() - GameTime::msTotalTimeSec;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Update()

    void TestGame::Render(){
        //blank screen w/ bg color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        rectangle.draw();
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg