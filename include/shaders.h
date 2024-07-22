#ifndef CXDG_SHADERS
#define CXDG_SHADERS

#include <glm/glm.hpp>

namespace cdxg_shaders {
    static const char *vs_source = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0);
}
)";
    static const char *fs_source = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}  
)";
    const char *fs_source_colored(glm::vec4 *color);
}

#endif