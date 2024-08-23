#include "strRawShaders.hh"

// Get shaders from linked and compiled .glsl files
// To get all the symbols names,
// run make bin/rawShaders.o then run objdump -x bin/rawShaders.o
extern const char const *__binary___assets_source_fs_glsl_start;
extern const char const *__binary___assets_source_vs_glsl_start;

namespace cdxg
{
    RawShaderDuo RawShaders::source = RawShaderDuo(__binary___assets_source_vs_glsl_start, __binary___assets_source_fs_glsl_start);

    RawShaderDuo::RawShaderDuo(const char const*vertexShader, const char const*fragmentShader) :
    msstrVertexShader(vertexShader),
    msstrFragmentShader(fragmentShader)
    {}

    const std::string *RawShaderDuo::FragmentShader(){
        return &msstrFragmentShader;
    }

    const std::string *RawShaderDuo::VertexShader(){
        return &msstrVertexShader;
    }
} // namespace cdxg