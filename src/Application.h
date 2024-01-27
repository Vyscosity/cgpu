#pragma once

#include <vector>
#include <memory>
#include <bgfx/bgfx.h>
#include <bgfx/defines.h>

#include "States/StateBase.h"
#include "Renderer/RenderMaster.h"

#include "Context.h"
#include "Camera.h"

class Application
{
    public:
        Application(std::string&& name);

        void runLoop(
            int argc,
            char** argv,
            bgfx::RendererType::Enum type = bgfx::RendererType::Count,
            uint16_t vendorId = BGFX_PCI_ID_NONE,
            uint16_t deviceId = 0,
            bgfx::CallbackI* callback = NULL,
            bx::AllocatorI* allocator = NULL
        );

        template<typename T, typename... Args>
        void pushState(Args&&... args)
        {
            m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            auto& s = m_states.back();
        }

        void popState();

        Camera& getCamera() { return m_camera; }

        //const sf::RenderWindow& getWindow() const { return m_context.window; }

        const BasicWindow& getWindow() const { return m_context.basicWindow; }


    private:
        void handleEvents();

        std::vector<std::unique_ptr<StateBase>> m_states;

        Context m_context;
        RenderMaster m_masterRenderer;
        Camera m_camera;


        bool m_isPopState = false;
};

