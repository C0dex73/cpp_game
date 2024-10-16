#include "shader.hh"
#include "strRawShaders.hh"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>


namespace cdxg {
    Shader::Shader(RawShaderDuo *pShaders):
    muiShaderProgramId(glCreateProgram()),
    mpcpVertexShader(pShaders->pVertexShader()),
    mpcpFragmentShader(pShaders->pFragmentShader()),
    mbLoaded(false)
    {}

    Shader::Shader(const char *const pstrVertexShader, const char *const pstrFragmentShader):
    muiShaderProgramId(glCreateProgram()),
    mpcpVertexShader(pstrVertexShader),
    mpcpFragmentShader(pstrFragmentShader),
    mbLoaded(false)
    {}

    Shader::~Shader()
    {
        glDeleteProgram(muiShaderProgramId);
    }

    Shader **const Shader::defaultShader(){
        return &mpDefault;
    }

    void Shader::Load()
    {
        if(mbLoaded) { return; }

        //compile vertex shader
        const char* vertexShader = mpcpVertexShader;
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
        glCompileShader(vertexShaderId);

        int sucess;
        char infoLog[512];
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &sucess);
        if(!sucess)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
        }

        //compile fragment shader
        const char* fragmentShader = mpcpFragmentShader;
        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
        glCompileShader(fragmentShaderId);

        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &sucess);
        if(!sucess)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
        }

        //link both shaders and shader program
        glAttachShader(muiShaderProgramId, vertexShaderId);
        glAttachShader(muiShaderProgramId, fragmentShaderId);
        glLinkProgram(muiShaderProgramId);

        //delete shaders
        glDetachShader(muiShaderProgramId, vertexShaderId);
        glDetachShader(muiShaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        mbLoaded = true;
    }

    void Shader::Use()
    {
        if(!mbLoaded) {
            throw std::runtime_error("A shader has been used before loaded.");
        }
        glUseProgram(muiShaderProgramId);
    }

    void Shader::setDefaultShader(Shader *const defaultShader)
    {
        if(mpDefault != nullptr) { delete mpDefault; }
        Shader::mpDefault = defaultShader;
    }

    Shader *Shader::mpDefault = nullptr;
} // namespace cdxg