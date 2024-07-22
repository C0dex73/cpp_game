#include <string>
#include <glm/glm.hpp>
#include "shaders.h"


const char *cdxg_shaders::fs_source_colored(glm::vec4 *color) {
    std::string s = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "\tFragColor = vec4(";
    s += std::to_string(color->x) + "f, ";
    s += std::to_string(color->y) + "f, ";
    s += std::to_string(color->z) + "f, ";
    s += std::to_string(color->w) + "f);\n}\0";
    return s.c_str();
} 