#ifndef CDXG_SHADER_CLASS
#define CDXG_SHADER_CLASS

#include <string>

namespace cdxg {
    class Shader {
        public:
        const unsigned int mShaderProgramId;
        Shader(std::string *pstrVertexShader, std::string *pstrFragmentShader);
        ~Shader();

    }; // class Shader
} // namespace cdxg

#endif // CDXG_SHADER_CLASS