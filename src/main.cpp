#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


/**
 * Handle window size change
 * @param window a pointer to a glfwwindow object to specify wich window changes size
 * @param width the new width of the window
 * @param height the new height to the window
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * The main function, called when the executable lauches
 */
int main(){

    // initialize glfw
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW.\r\n" );
        return -1;
    }

    // opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates the window
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Test1", NULL, NULL);
    if( !window ) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\r\n");
        glfwTerminate();
        return -1;
    }

    // tells opengl wich window to operate on
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // initialize glew
    if (glewInit() != 0) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // initialize Uinput
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    //^ Main loop
    do{
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    //exit
    glfwTerminate();
    return 0;
}