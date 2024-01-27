#include "Application.h"
#include "States/PlayingState.h"
#include "Clock.h"

#include <SDL.h>
#include <SDL_system.h>
#include <iostream>

//#include <chrono>
//#include <thread>

Application::Application(std::string&& name)
{
    pushState<StatePlaying>(*this);
}

void sleepForTargetFrameRate(float targetFrameRate)
{
    // Calculate the target frame time in milliseconds
    Uint32 targetFrameTime = static_cast<Uint32>(1000.0f / targetFrameRate);

    // Delay for the remaining time to achieve the target frame rate
    SDL_Delay(targetFrameTime);
}

void Application::runLoop(int argc, char** argv, bgfx::RendererType::Enum type, uint16_t vendorId, uint16_t deviceId, bgfx::CallbackI* callback, bx::AllocatorI* allocator)
{
    //sf::Clock dtTimer;
    Clock timer;
                      unsigned int frameCount = 0;
                      float fpsTimer = 0.0f;

                      
    m_context.basicWindow.clear();

    m_context.basicWindow.clear();

    while (m_context.basicWindow.isOpen() && !m_states.empty())
    {
        auto deltaTime = timer.restart();
        auto& state = *m_states.back();

        state.handleInput();
        state.update(deltaTime);
        m_camera.update();

        state.render(m_masterRenderer);
        m_masterRenderer.finishRender(m_context.basicWindow, m_camera); //masterRenderer throw window and camera RENDERS THE QUADS <<

                        // Update FPS
                        frameCount++;
                        fpsTimer += deltaTime;
                        if (fpsTimer >= 1.0f)  // Print every second
                        {
                            float fps = static_cast<float>(frameCount) / fpsTimer;

                            // Print FPS to console
                            std::cout << "FPS: " << static_cast<int>(fps) << std::endl;

                            frameCount = 0;
                            fpsTimer = 0.0f;
                        }

                        //sleepForTargetFrameRate(60000.0f);


        handleEvents();
        if (m_isPopState)
        {
            m_isPopState = false;
            m_states.pop_back();
        }
    }
}

void Application::handleEvents()
{
    //sf::Event e;

    //const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_Event e;

    while (SDL_PollEvent(&e))//m_context.window.pollEvent(e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                m_context.basicWindow.close();
                break;

            case SDL_KEYDOWN:  //* how elegant :3 *//
                switch(e.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE: 
                        m_context.basicWindow.close();
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


void Application::popState()
{
    m_isPopState = true;
}
