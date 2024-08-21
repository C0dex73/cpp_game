#version 450 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec3 aColor;

out vec3 vertexColor;

int main(){
    vertexColor = vec3(aColor);
    gl_position = vec4(aPos.xy, 0, 1.0);
}