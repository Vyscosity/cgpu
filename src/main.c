#include <stdio.h>
#include <bgfx/c99/bgfx.h>
#include <SDL.h>
#include <SDL_syswm.h>

static const int _width = 1280;
static const int _height = 720;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        //return 1;
    }

    void* native_window_handle = NULL;

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
    wl_egl_window* win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
    if (!win_impl)
    {
        int width, height;
        SDL_GetWindowSize(_window, &width, &height);
        struct wl_surface* surface = wmi.info.wl.surface;
        if (!surface)
            native_window_handle = NULL;
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

    bgfx_platform_data_t pd;
    //bgfx::PlatformData pd;
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

    bgfx_set_platform_data(&pd);
    //bgfx::setPlatformData(pd);

    // Render an empty frame
    //bgfx::renderFrame();
    //bgfx_render_frame = true;

    //bgfx::Init init;
    bgfx_init_t init;
    bgfx_init_ctor(&init);

    //init.type = bgfx::RendererType::OpenGL;
    //init.resolution.reset = BGFX_RESET_MSAA_X16;
    // Set memory configuration
    bgfx_init(&init);

    //bgfx::init(init);
    bgfx_set_view_rect(0, 0, 0, _width, _height);

    uint32_t clearColour = 255 << 24 | 128 << 16 | 0 << 8 | 255;

    // Set clear color to red
    bgfx_set_view_clear(0, BGFX_CLEAR_COLOR, clearColour, 1.0f, 0);

    bgfx_touch(0);

    // Main loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        //bgfx::touch(0);
        //bgfx_touch
        //bgfx::frame();
        bgfx_frame(false);

        // Present the renderer
        //SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyWindow(window);
    
    bgfx_shutdown();

    SDL_Quit();

    return 0;
}
