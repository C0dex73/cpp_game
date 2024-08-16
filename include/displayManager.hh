#ifndef CDXG_DISPLAY_MANAGER
#define CDXG_DISPLAY_MANAGER

#include <GLFW/glfw3.h>
#include <string>

namespace cdxg {

    class DisplayManager {
        public:
        inline static GLFWwindow *mpsWindow;
        static void CreateWindow(int width, int height, std::string title);
        static void CloseWindow();
        DisplayManager() = delete;
    }; // class DisplayManager

} // namespace cdxg

#endif