#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>
#include <vector>
#include <math.h>


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

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 4.5
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates the window
    GLFWwindow *window = glfwCreateWindow(800, 800, "CDXG", NULL, NULL);
    if( !window ) {
        fprintf(stderr, "Failed to open GLFW window.\r\n");
        glfwTerminate();
        return -1;
    }

    // tells opengl wich window to operate on
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    //Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\r\n");
        return -1;
    }   

    // initialize Uinput
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    
    std::chrono::steady_clock::time_point begin;
    //^ Main loop
    do{
        begin = std::chrono::steady_clock::now();
        glClear(GL_COLOR_BUFFER_BIT);
        

        glfwSwapBuffers(window);
        glfwPollEvents();

        while(since(begin).count() < 16) {}
    }while( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    //exit
    glfwTerminate();
    return 0;
}