#pragma once

#include <bgfx/bgfx.h>

struct Vertex
{
    float x;
    float y;
    float z;
    uint16_t u;
    uint16_t v;

    static void init()
    {
        ms_layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
            .end();
    }
    static bgfx::VertexLayout ms_layout;

};
