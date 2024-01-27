#include "BasicWindow.h"

#include <iostream>
#include <memory>

#include <SDL_syswm.h>
#include <bgfx/platform.h>

BasicWindow::BasicWindow()
{
}
void BasicWindow::create(){
    // Initialize SDL systems
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error : " << SDL_GetError();
        return;
    }
    else {
        //Create a window
        basicWindow = SDL_CreateWindow("hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (basicWindow == nullptr) {
            std::cout << "SDL Window could not be created! : " << SDL_GetError();
            SDL_Quit();
            return;
        }
    }

    SDL_GL_SetSwapInterval(0); //DISABLE VSYNC
    // tell SDL to capture our mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);


    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(basicWindow, &wmi)) {
        //return 1;
    }

    void* native_window_handle = nullptr;

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
    wl_egl_window* win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
    if (!win_impl)
    {
        int width, height;
        SDL_GetWindowSize(_window, &width, &height);
        struct wl_surface* surface = wmi.info.wl.surface;
        if (!surface)
            native_window_handle = nullptr;
        win_impl = wl_egl_window_create(surface, width, height);
        SDL_SetWindowData(_window, "wl_egl_window", win_impl);
    }
    native_window_handle = (void*)(uintptr_t)win_impl;
#		else
    native_window_handle = (void*)wmi.info.x11.window;
#		endif
#	elif BX_PLATFORM_OSX || BX_PLATFORM_IOS
    native_window_handle = wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
    native_window_handle = wmi.info.win.window;
#   elif BX_PLATFORM_ANDROID
    native_window_handle = wmi.info.android.window;
#	endif // BX_PLATFORM_

    bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
    pd.ndt = wmi.info.wl.display;
#		else
    pd.ndt = wmi.info.x11.display;
#		endif
#	else
    pd.ndt = NULL;
#	endif // BX_PLATFORM_
    pd.nwh = native_window_handle;

    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData(pd);

    // Render an empty frame
    bgfx::renderFrame();

    bgfx::Init init;
    //init.type = bgfx::RendererType::Vulkan;
    //init.type == bgfx::RendererType::Direct3D11;

    bgfx::init(init);
    
    open = true;
}

void BasicWindow::close()
{
    open = false;
}

bool BasicWindow::pollEvent(SDL_Event e)
{
    return SDL_PollEvent(&e);
}

void BasicWindow::display()
{
    // Check if the window is minimized, if yes, do not render
    bgfx::frame(); // Render a frame when the window is not minimized.
    
}

bool BasicWindow::isOpen()
{
	return open;
}

void BasicWindow::clear()
{
    bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
    uint32_t clearColour = 0 << 24 | 0 << 16 | 0 << 8 | 255;
    uint32_t blue = 0x6495edff;
    bgfx::setViewClear(0,
        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        blue, 1.0f, 0);
}
