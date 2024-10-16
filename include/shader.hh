#ifndef CDXG_SHADER_CLASS
#define CDXG_SHADER_CLASS

#include <string>
#include "strRawShaders.hh"
#include "displayManager.hh"

namespace cdxg {
    class Shader {
        public:
        Shader(RawShaderDuo *pShaders);
        Shader(const char *const pstrVertexShader, const char *const pstrFragmentShader);
        ~Shader();
        void Use();
        void Load();
        static Shader **const defaultShader();
        friend void DisplayManager::CreateWindow(int width, int height, std::string title);
        private:
        static void setDefaultShader(Shader *const defaultShader);
        static Shader *mpDefault;
        bool mbLoaded;
        const unsigned int muiShaderProgramId;
        const char *const mpcpVertexShader;
        const char *const mpcpFragmentShader;
    }; // class Shader
} // namespace cdxg

#endif // CDXG_SHADER_CLASS