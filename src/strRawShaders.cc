#include "strRawShaders.hh"

namespace cdxg
{
    RawShaderDuo::RawShaderDuo(char *pcVs[2], char *pcFs[2]):
    mpcVertexShader(pcVs[0]),
    mpcFragmentShader(pcFs[0])
    {
        size_t vsSize = pcVs[1] - pcVs[0];
        pcVs[0][vsSize-1] = ""[0];

        size_t fsSize = pcFs[1] - pcFs[0];
        pcFs[0][fsSize-1] = ""[0];
    }

    char *RawShaderDuo::pVertexShader(){
        return mpcVertexShader;
    }
    char *RawShaderDuo::pFragmentShader(){
        return mpcFragmentShader;
    }

    RawShaderDuo RawShaders::source = RawShaderDuo(
       (char*[2]){ _binary___assets_source_vs_glsl_start, _binary___assets_source_vs_glsl_end},
       (char*[2]){ _binary___assets_source_fs_glsl_start, _binary___assets_source_fs_glsl_end});
} // namespace cdxg