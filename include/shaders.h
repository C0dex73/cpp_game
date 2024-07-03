#ifndef CXDG_SHADERS
#define CXDG_SHADERS

#include <string>

namespace cxdg_shaders {
    const char *vs_source = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0);
}
)";

    const char *fs_source = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}  
)";
}

#endif