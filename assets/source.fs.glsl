#version 450 core
in vec3 vertexColor;

int main(){
    gl_FragColor = vec4(vertexColor, 1.0);
}