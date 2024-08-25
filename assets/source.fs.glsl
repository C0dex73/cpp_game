#version 450 core
layout(location = 0) out vec4 diffuseColor;
in vec3 vertexColor;

void main(){
    diffuseColor = vec4(vertexColor, 0.0);
};