#include <stdio.h>
#include <stdlib.h>

#if _WIN32 || _WIN64
#include <windows.h>
#endif

// TODO: Potentially add Linux threading support...

#include "sys/sys.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "ui/nuklear.h"
#include "ui/nuklear_glfw_gl3.h"

#define INITIAL_WIDTH 1200
#define INITIAL_HEIGHT 800
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

static void error_callback(int e, const char *d)
{
	printf("[ERROR]: %d: %s\n", e, d);
}

#if _WIN32 || _WIN64
DWORD WINAPI EmulatorThread(void* data)
{
	System* sys = (System*)data;
	sys_boot(sys);
}
#endif

// TODO: Potentially add Linux threading...

int main(int argc, char* argv[]) 
{
	if (argv[1] == NULL)
	{
		printf("[Error]: You must provide the path to a ROM file\n");
		exit(1);
	}

	// Setup the GUI
	static GLFWwindow *win;
	int width, height = 0;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stdout, "[GLFW]: failed to initialize\n");
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	win = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Emu64", NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwGetWindowSize(win, &width, &height);

	// Setup OpenGL
	glViewport(0, 0, INITIAL_WIDTH, INITIAL_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "[ERROR]: Failed to setup GLEW\n");
		exit(1);
	}

	struct nk_context *ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);

	// Fonts
	{
		struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		// TODO: Add custom fonts
		nk_glfw3_font_stash_end();
	}

	// Background color
	struct nk_colorf bg;
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

	// Setup the emulator system
	System* system = sys_create();
	
	// GUI
	while (!glfwWindowShouldClose(win))
	{
		// Input
		glfwPollEvents();
		nk_glfw3_new_frame();

		// The main view
		if (nk_begin(ctx, "Main", nk_rect(0, 0, width, height), NULL))
		{
			// Menubar
			nk_menubar_begin(ctx);
			nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
			nk_layout_row_push(ctx, 45);
			if (nk_menu_begin_label(ctx, "File", NK_TEXT_LEFT, nk_vec2(120, 200)))
			{
				nk_layout_row_dynamic(ctx, 25, 1);
				if (nk_menu_item_label(ctx, "Load Rom", NK_TEXT_LEFT))
				{
					sys_load_rom(system, argv[1]); // TODO: File picker...

					#if _WIN32 || _WIN64
						HANDLE thread = CreateThread(NULL, 0, EmulatorThread, system, 0, NULL);
						if (thread)
						{
							// TODO: Potentially do more with the thread...
						}
						else
						{
							printf("[ERROR]: Emulator thread failed to run!\n");
						}
					#endif
					// TODO: Potentially add Linux threading...
				}
				nk_menu_end(ctx);
			}
			nk_menubar_end(ctx);
		}

		nk_end(ctx);
		// Draw
		glfwGetWindowSize(win, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bg.r, bg.g, bg.b, bg.a);
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		glfwSwapBuffers(win);
	}

	// Cleanup
	sys_destroy(system);

	nk_glfw3_shutdown();
	glfwTerminate();
	return 0;
}
