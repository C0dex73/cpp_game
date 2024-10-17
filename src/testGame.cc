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
        GameTemplate(initialWidth, initialHeight, initialTitle),
        vertices({
            VertexRGB(-0.2, -0.2, 1.0, 0.0, 0.0),
            VertexRGB(0.2, 0.2, 0.0, 1.0, 0.0),
            VertexRGB(-0.2, 0.2, 0.0, 0.0, 1.0),
            VertexRGB(0.2, -0.2, 1.0, 1.0, 1.0)
        }),
        indices({0, 1, 2, 0, 1, 3})
        {}

    TestGame::~TestGame(){}

    void TestGame::Initialize(){
        // initialize Uinput
        glfwSetInputMode(DisplayManager::mpsWindow, GLFW_STICKY_KEYS, 0);
        //initialize GameTime
        GameTime::msDeltaTimeSec = 0.0f;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Initialize()

    void TestGame::addRectangle(){
        rectangles.push_back(Displayable<VertexRGB>());
        ++state;
        rectangles[state].setVerticesIndices(indices, false);
        rectangles[state].setVertices(vertices, false);
        rectangles[state].setShader(Shader::defaultShader());
        rectangles[state].load();
    }

    void TestGame::processInput(){
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_ADD) == GLFW_PRESS && oldAddButtonState == GLFW_RELEASE){
            addRectangle();
        }
        if(state == -1) { return; }

        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_LEFT) == GLFW_PRESS){
            rectangles[state].move(-0.005, 0.0);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_RIGHT) == GLFW_PRESS){
            rectangles[state].move(0.005, 0.0);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_UP) == GLFW_PRESS){
            rectangles[state].move(0.0, 0.005);
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_DOWN) == GLFW_PRESS){
            rectangles[state].move(0.0, -0.005);
        }
        
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && oldSubButtonState == GLFW_RELEASE){
            rectangles.erase(rectangles.begin() + state);
            if(rectangles.size() == 0) { state = -1; }
        }
        if(glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_SPACE) == GLFW_PRESS && oldSpaceButtonState == GLFW_RELEASE){
            ++state;
        }
        if(state >= rectangles.size()) { state = 0; }
    }

    void TestGame::Update(){
        //update GameTime
        GameTime::msDeltaTimeSec = glfwGetTime() - GameTime::msTotalTimeSec;
        GameTime::msTotalTimeSec = glfwGetTime();

        processInput();
        oldAddButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_ADD);
        oldSubButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_KP_SUBTRACT);
        oldSpaceButtonState = glfwGetKey(DisplayManager::mpsWindow, GLFW_KEY_SPACE);
    } // void Update()

    void TestGame::Render(){
        //blank screen w/ bg color
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < rectangles.size(); ++i){
            rectangles[i].draw();
        }
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg