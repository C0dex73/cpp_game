#include "testGame.hh"
#include "displayManager.hh"
#include "gameTime.hh"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cdxg {

    TestGame::TestGame(int initialWidth, int initialHeight, std::string initialTitle):
        GameTemplate(initialWidth, initialHeight, initialTitle){}

    void TestGame::Initialize(){
        // initialize Uinput
        glfwSetInputMode(DisplayManager::mpsWindow, GLFW_STICKY_KEYS, 0);

        //initialize GameTime
        GameTime::msDeltaTimeSec = 0.0f;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Initialize()

    void TestGame::LoadComponents(){

    } // void LoadComponents()

    void TestGame::Update(){
        //update GameTime
        GameTime::msDeltaTimeSec = glfwGetTime() - GameTime::msTotalTimeSec;
        GameTime::msTotalTimeSec = glfwGetTime();
    } // void Update()

    void TestGame::Render(){
        //blank screen w/ bg color
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // display the current frame and init the next one
        glfwSwapBuffers(DisplayManager::mpsWindow);
    } // void Render()

} // namespace cdxg