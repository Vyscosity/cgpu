#include "ShaderLoader.h"

#include "../Util/FileUtil.h"

#include <stdexcept>
#include <iostream>

#include <bx/math.h>
#include <bgfx/platform.h>

#include <glm/glm.hpp>
#include <fstream>
#include <bx/string.h>
//#include <GL/glew.h>
//#include <bgfx/bgfx.h>

namespace
{
    const bgfx::Memory* loadMemory(const char* filename)
    {
        std::cout << filename << "\n";
        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            std::cout << "ERROR\n";
            throw std::runtime_error("Failed to open file: ");
        }
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        const bgfx::Memory* mem = bgfx::alloc(uint32_t(size + 1));
        if (file.read((char*)mem->data, size))
        {
            mem->data[mem->size - 1] = '\0';
            return mem;
        }
        return nullptr;
    }
    /*
    GLuint compileShader(const GLchar* source, GLenum shaderType)
    {
        auto shaderID = glCreateShader(shaderType);

        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        GLint isSuccess = 0;
        GLchar infoLog[512];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
        if(!isSuccess)
        {
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            throw std::runtime_error ("Unable to load a shader: " + std::string(infoLog));
        }

        return shaderID;
    }
    */
    

    bgfx::ShaderHandle linkProgram(const char* shader)
    {
        /*
        auto id = glCreateProgram();

        glAttachShader(id, vertexShaderID);
        glAttachShader(id, fragmentShaderID);

        glLinkProgram(id);

        return id;
        */
        return bgfx::createShader(loadMemory(shader));

    }
}

bgfx::ProgramHandle loadShaders(const char* vsPath, const char* fsPath)
{
    /*
    auto vertexSource   = getFileContents("Shaders/" + vertexShader     + ".glsl");
    auto fragmentSource = getFileContents("Shaders/" + fragmentShader   + ".glsl");

    auto vertexShaderID     = compileShader(vertexSource.c_str(),   GL_VERTEX_SHADER);
    auto fragmentShaderID   = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return shaderID;
    */

    char vsName[512];
    char fsName[512];

    const char* shaderPath = "???";

    switch (bgfx::getRendererType())
    {
    case bgfx::RendererType::Noop:
    case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
        //case bgfx::RendererType::Agc:
    case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
    case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
    case bgfx::RendererType::Nvn:        shaderPath = "shaders/nvn/";   break;
    case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
    case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
    case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
        //case bgfx::RendererType::WebGPU:     shaderPath = "shaders/spirv/"; break;

    case bgfx::RendererType::Count:
        //BX_ASSERT(false, "You should not be here!");
        break;
    }

    bx::strCopy(vsName, BX_COUNTOF(vsName), shaderPath);
    std::string v = std::string(vsPath) + ".bin";
    std::cout << v;
    bx::strCat(vsName, BX_COUNTOF(vsName), v.c_str());

    bx::strCopy(fsName, BX_COUNTOF(fsName), shaderPath);
    std::string f = std::string(fsPath) + ".bin";
    bx::strCat(fsName, BX_COUNTOF(fsName), f.c_str());

    bgfx::ShaderHandle vs = linkProgram(vsName);
    bgfx::ShaderHandle fs = linkProgram(fsName);
    bgfx::ProgramHandle handle = bgfx::createProgram(vs, fs, true);
    // // // // // // // / /

    //bgfx::ShaderHandle handle = bgfx::createShader(loadMem(_reader, filePath));
    //bgfx::setName(handle, _name);

    return handle;
    //bgfx::ShaderHandle vs = loadShader(vsName);
    //bgfx::ShaderHandle fs = loadShader(fsName);
    //return bgfx::createProgram(vs, fs, true);
}

