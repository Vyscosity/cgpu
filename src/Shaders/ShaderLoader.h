#pragma once

#include <string>
//#include <GL/glew.h>
#include <bgfx/bgfx.h>

bgfx::ProgramHandle loadShaders(const char* vsPath, const char* fsPath);