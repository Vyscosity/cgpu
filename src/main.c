#include <stdio.h>

#include <bgfx/c99/bgfx.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include "config.h"

#define MATH_3D_IMPLEMENTATION
#include "math_3d.h"

typedef struct {
    int width;
    int height;
    const char* title;
    SDL_Window* window;
} Model;

static Model model;
static Model* g = &model;













typedef struct PosColourVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
} PosColourVertex;

static PosColourVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000},
    { 1.0f,  1.0f,  1.0f, 0xff0000ff},
    {-1.0f, -1.0f,  1.0f, 0xff00ff00},
    { 1.0f, -1.0f,  1.0f, 0xff00ffff},
    {-1.0f,  1.0f, -1.0f, 0xffff0000},
    { 1.0f,  1.0f, -1.0f, 0xffff00ff},
    {-1.0f, -1.0f, -1.0f, 0xffffff00},
    { 1.0f, -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t cubeTriList[] =
{
    2, 1, 0,
    2, 3, 1,
    5, 6, 4,
    7, 6, 5,
    4, 2, 0,
    6, 2, 4,
    3, 5, 1,
    3, 7, 5,
    1, 4, 0,
    1, 5, 4,
    6, 3, 2,
    7, 3, 6,
};





























bgfx_shader_handle_t loadShader(const char* FILENAME)
{
    const char* shaderPath = "???";

    //dx11/  dx9/   essl/  glsl/  metal/ pssl/  spirv/
    bgfx_shader_handle_t invalid = BGFX_INVALID_HANDLE;

    switch (bgfx_get_renderer_type()) {
    case BGFX_RENDERER_TYPE_NOOP:
    case BGFX_RENDERER_TYPE_DIRECT3D9:     shaderPath = "shaders/dx9/";   break;
    case BGFX_RENDERER_TYPE_DIRECT3D11:
    case BGFX_RENDERER_TYPE_DIRECT3D12:    shaderPath = "shaders/dx11/";  break;
    case BGFX_RENDERER_TYPE_GNM:           shaderPath = "shaders/pssl/";  break;
    case BGFX_RENDERER_TYPE_METAL:         shaderPath = "shaders/metal/"; break;
    case BGFX_RENDERER_TYPE_OPENGL:        shaderPath = "shaders/glsl/";  break;
    case BGFX_RENDERER_TYPE_OPENGLES:      shaderPath = "shaders/essl/";  break;
    case BGFX_RENDERER_TYPE_VULKAN:        shaderPath = "shaders/spirv/"; break;
    case BGFX_RENDERER_TYPE_NVN:
    //case BGFX_RENDERER_TYPE_WEBGPU:
    case BGFX_RENDERER_TYPE_COUNT:         return invalid; // count included to keep compiler warnings happy
    }

    size_t shaderLen = strlen(shaderPath);
    size_t fileLen = strlen(FILENAME);
    char* filePath = (char*)malloc(shaderLen + fileLen + 1);
    memcpy(filePath, shaderPath, shaderLen);
    memcpy(&filePath[shaderLen], FILENAME, fileLen);
    filePath[shaderLen + fileLen] = 0;    // properly null terminate

    FILE* file = fopen(filePath, "rb");

    if (!file) {
        return invalid;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    const bgfx_memory_t* mem = bgfx_alloc(fileSize + 1);
    fread(mem->data, 1, fileSize, file);
    mem->data[mem->size - 1] = '\0';
    fclose(file);

    return bgfx_create_shader(mem);
}

void create_window()
{
    g->height = WINDOW_HEIGHT;
    g->width = WINDOW_WIDTH;
    g->title = TITLE;
    SDL_Window* window = NULL;

    Uint32 flags = 0;// FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0;
    if (FULLSCREEN)
    {
        flags = SDL_WINDOW_FULLSCREEN;
        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
            // Handle getting display mode error
            SDL_Quit();
            return -1;
        }
        g->width = dm.w;
        g->height = dm.h;
    }


    g->window = SDL_CreateWindow(g->title, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        g->width, g->height,
        SDL_WINDOW_SHOWN);
}

void create_graphics()
{
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(g->window, &wmi)) {
        return 1;
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

    bgfx_init_t init;
    bgfx_init_ctor(&init);

    //init.type = bgfx::RendererType::OpenGL;
    init.resolution.width = g->width;
    init.resolution.height = g->height;
    init.type = BGFX_RENDERER_TYPE_DIRECT3D12;
    //init.resolution.reset = BGFX_RESET_MSAA_X16;

    bgfx_init(&init);

    printf("using %s renderer\n", bgfx_get_renderer_name(bgfx_get_renderer_type()));

    //uint32_t clearColour = 255 << 24 | 128 << 16 | 0 << 8 | 255;

    bgfx_set_view_clear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x222222FF, 1.0f, 0);
    bgfx_touch(0);
}

int main(int argc, char* argv[]) {
    // WINDOW INITIALIZATION //
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }
    create_window();
    if (!g->window) {
        SDL_Quit();
        return -1;
    }
    // GRAPHICS INITIALIZATION //
    create_graphics();




















    bgfx_vertex_layout_t pcvDecl;

    bgfx_vertex_layout_begin(&pcvDecl, bgfx_get_renderer_type());
    bgfx_vertex_layout_add(&pcvDecl, BGFX_ATTRIB_POSITION, 3, BGFX_ATTRIB_TYPE_FLOAT, false, false);
    bgfx_vertex_layout_add(&pcvDecl, BGFX_ATTRIB_COLOR0, 4, BGFX_ATTRIB_TYPE_UINT8, true, false);
    bgfx_vertex_layout_end(&pcvDecl);

    const bgfx_memory_t* vbm = bgfx_make_ref(cubeVertices, sizeof(PosColourVertex) * 8);
    bgfx_vertex_buffer_handle_t vbh = bgfx_create_vertex_buffer(vbm, &pcvDecl, BGFX_BUFFER_NONE);
    
    const bgfx_memory_t* ibm = bgfx_make_ref(cubeTriList, sizeof(uint16_t) * 12 * 3);
    bgfx_index_buffer_handle_t ibh = bgfx_create_index_buffer(ibm, BGFX_BUFFER_NONE);

    bgfx_shader_handle_t vsh = loadShader("vs_cubes.bin");
    printf("shader handle %i created for vs_cubes.bin\n", vsh.idx);
    if (vsh.idx == USHRT_MAX)
    {
        printf("*** shader model not supported or file not found ****\n");
        bgfx_shutdown();
        return -1;
    }

    bgfx_shader_handle_t fsh = loadShader("fs_cubes.bin");
    printf("shader handle %i created for fs_cubes.bin \n", fsh.idx);
    if (fsh.idx == USHRT_MAX)
    {
        printf("*** shader model not supported or file not found ****\n");
        bgfx_shutdown();
        return -1;
    }

    bgfx_program_handle_t program = bgfx_create_program(vsh, fsh, true);
    printf("program handle %i created\n", program.idx);




























    unsigned int counter = 0;

    // OUTER LOOP //
    bool quit = false;
    while (!quit) {
    bgfx_set_view_rect(0, 0, 0, g->width, g->height);







    vec3_t at = { 0.0f, 0.0f,  0.0f };
    vec3_t eye = (vec3_t){ sin((float)counter / 100) * 8, 2, cos((float)counter / 100) * 8 };
    vec3_t up = { 0.0f, 1.0f, 0.0f };
    mat4_t view;

    view = m4_look_at(eye, at, up);

    mat4_t proj;
    proj = m4_perspective(60.0f, (float)(g->width) / (float)(g->height), 0.01f, 1000.f);

    bgfx_set_view_transform(0, &view, &proj);

    mat4_t mtx, mtx_x, mtx_y;
    mtx_y = m4_rotation_y(counter * 0.007f);
    mtx_x = m4_rotation_x(counter * 0.01f);
    mtx = m4_mul(mtx_x, mtx_y);
    bgfx_set_transform(&mtx, 1);

    bgfx_set_vertex_buffer(0, vbh, 0, 8);
    bgfx_set_index_buffer(ibh, 0, 12 * 3);

    bgfx_submit(0, program, 0, BGFX_DISCARD_ALL);

    mtx = m4_mul(mtx_x, mtx_y);

    mtx = m4_translation((vec3_t) { 3, 0, 0 });
    bgfx_set_transform(&mtx, 1);
    bgfx_set_vertex_buffer(0, vbh, 0, 8);
    bgfx_set_index_buffer(ibh, 0, 12 * 3);

    bgfx_submit(0, program, 0, BGFX_DISCARD_ALL);






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
        SDL_Delay(10);
        counter++;
        // Present the renderer
        //SDL_RenderPresent(renderer);
    }

    // Cleanup
    
    bgfx_destroy_program(program);

    bgfx_destroy_index_buffer(ibh);
    bgfx_destroy_vertex_buffer(vbh);
    bgfx_shutdown();

    SDL_DestroyWindow(g->window);
    SDL_Quit();

    return 0;
}
