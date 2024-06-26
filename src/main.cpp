#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Main game loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();

        // Rendering code goes here

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    glfwTerminate();

    return 0;
}
