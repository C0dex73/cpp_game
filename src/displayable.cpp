#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include "displayable.h"
#include "triangle.h"
#include "shaders.h"

cdxg::Displayable::Displayable(glm::vec2 *_vertices, unsigned int _verticesCount)
    : vertices(_vertices), shaderProgramID(glCreateProgram()), verticesCount(_verticesCount){

    //openGL Shaders processing
    VshaderID = glCreateShader(GL_VERTEX_SHADER);
    FshaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VshaderID, 1, &cxdg_shaders::vs_source, NULL);
    glCompileShader(VshaderID);
    int success;
    char infoLog[512];
    glGetShaderiv(VshaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(VshaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glShaderSource(FshaderID, 1, &cxdg_shaders::fs_source, NULL);
    glCompileShader(FshaderID);
    glGetShaderiv(FshaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(FshaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgramID, VshaderID);
    glAttachShader(shaderProgramID, FshaderID);
    glLinkProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Free memory
    glDeleteShader(VshaderID);
    glDeleteShader(FshaderID);

    //openGl objects init
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(*vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 2*sizeof(vertices->x), (void*)0);
    glEnableVertexAttribArray(0);
}

std::ostream& cdxg::operator<<(std::ostream& os, cdxg::Displayable const d){
    os << "Vertices : " << std::endl;
    for(unsigned int i = 0; i < d.verticesCount; ++i) {
        os << "Vertex " << i << " : X=" << d.vertices[i].x << " | Y=" << d.vertices[i].y << std::endl;
    }
    return os;
}

void cdxg::Displayable::rotate(float angle){
    for(unsigned int i = 0; i < verticesCount; i++){
        vertices[i] = glm::rotate(vertices[i], angle);
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(*vertices), vertices, GL_DYNAMIC_DRAW);
}

void cdxg::Displayable::draw(){
    glUseProgram(shaderProgramID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}