#include "displayManager.hh"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>

namespace cdxg {

    void DisplayManager::CreateWindow(int width, int height, std::string title){
        // initialize glfw
        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW.\r\n" );
            return;
        } // if failed glfw init
        
        // opengl context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3 core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // creates the window
        mpsWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if( !mpsWindow ) {
            fprintf(stderr, "Failed to open GLFW window.\r\n");
            glfwTerminate();
            return;
        } // if no window

        //make the new window focused and not resizable
        glfwFocusWindow(mpsWindow);
        glfwWindowHint(GLFW_RESIZABLE, 0);

        //init opengl
        glfwMakeContextCurrent(mpsWindow);
        glViewport(0, 0, 800, 800);
    } // void CloseWindow()

    void DisplayManager::CloseWindow(){
        glfwTerminate();
    } // void CloseWindow()

} // namespace cdxg