#ifndef CDXG_SHADER_CLASS
#define CDXG_SHADER_CLASS

#include <string>
#include "strRawShaders.hh"

namespace cdxg {
    class Shader {
        public:
        const std::string *mpstrVertexShader;
        const std::string *mpstrFragmentShader;
        const unsigned int muiShaderProgramId;
        Shader(RawShaderDuo *pShaders);
        Shader(const std::string *pstrVertexShader, const std::string *pstrFragmentShader);
        ~Shader();
        private:
        void ShaderInitializer();
    }; // class Shader
} // namespace cdxg

#endif // CDXG_SHADER_CLASS