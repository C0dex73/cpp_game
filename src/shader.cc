#include "shader.hh"
#include "strRawShaders.hh"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace cdxg {

    Shader::Shader(RawShaderDuo *pShaders):
    muiShaderProgramId(glCreateProgram())
    {
        mpstrVertexShader = pShaders->VertexShader();
        mpstrFragmentShader = pShaders->FragmentShader();
    }

    Shader::Shader(const std::string *pstrVertexShader, const std::string *pstrFragmentShader):
    muiShaderProgramId(glCreateProgram())
    {
        mpstrVertexShader = pstrVertexShader;
        mpstrFragmentShader = pstrFragmentShader;
    }

    Shader::~Shader()
    {
        glDeleteProgram(muiShaderProgramId);
    }

    void Shader::Load()
    {
        //compile vertex shader
        const char* vertexShader = mpstrVertexShader->c_str();
        unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
        glCompileShader(vertexShaderId);

        //compile fragment shader
        const char* fragmentShader = mpstrFragmentShader->c_str();
        unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
        glCompileShader(fragmentShaderId);

        //TODO : handle shaders compile error

        //link both shaders and shader program
        glAttachShader(muiShaderProgramId, vertexShaderId);
        glAttachShader(muiShaderProgramId, fragmentShaderId);
        glLinkProgram(muiShaderProgramId);

        //delete shaders
        glDetachShader(muiShaderProgramId, vertexShaderId);
        glDetachShader(muiShaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    void Shader::Use()
    {
        glUseProgram(muiShaderProgramId);
    }

} // namespace cdxg