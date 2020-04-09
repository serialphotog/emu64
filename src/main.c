#include <stdio.h>
#include <stdlib.h>

#if _WIN32 || _WIN64
#include <windows.h>
#endif

// TODO: Potentially add Linux threading support...

#include "emu64.h"
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
#define DEBUG_INITIAL_HEIGHT 450
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

HANDLE thread;
void run_emulator(System* system)
{
	thread = CreateThread(NULL, 0, EmulatorThread, system, 0, NULL);

	if (thread)
	{

	}
	else
	{
		printf("[ERROR]: Emulator thread failed to run!\n");
	}
}
#endif

// TODO: Potentially add Linux threading...

EmuFlags* flags_create()
{
    EmuFlags* flags = calloc(1, sizeof(EmuFlags));
    flags->debugMode = 1;
    flags->singleStepMode = 0;
    return flags;
}

void flags_destroy(EmuFlags* flags)
{
    free(flags);
}

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
	EmuFlags* flags = flags_create();
	System* system = sys_create(flags);
	
	// GUI
	while (!glfwWindowShouldClose(win))
	{
		// Input
		glfwPollEvents();
		nk_glfw3_new_frame();

		// The main view
		if (nk_begin(ctx, "Main", nk_rect(0, 0, 720, 576), NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE))
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
					// TODO: File picker...
					sys_load_rom(system, argv[1]);
					run_emulator(system);
				}

				if (nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT))
				{
					#if _WIN32 || _WIN64
						TerminateThread(thread, 0);
					#endif
					glfwSetWindowShouldClose(win, GLFW_TRUE);
				}
				nk_menu_end(ctx);
			}

			nk_layout_row_push(ctx, 60);
			if (nk_menu_begin_label(ctx, "Emulator", NK_TEXT_LEFT, nk_vec2(120, 250)))
			{
				nk_layout_row_dynamic(ctx, 25, 1);
				if (nk_menu_item_label(ctx, "Stop Emulation", NK_TEXT_LEFT))
				{
					#if _WIN32 || _WIN64
						if (thread)
							TerminateThread(thread, 0);
					#endif
				}

				nk_checkbox_label(ctx, "Enable Debug", &flags->debugMode);
				nk_menu_end(ctx);
			}
			nk_menubar_end(ctx);
		}
		nk_end(ctx);

		if (flags->debugMode)
		{
			if (nk_begin(ctx, "Debug", nk_rect(0, height - DEBUG_INITIAL_HEIGHT, width, DEBUG_INITIAL_HEIGHT), 
				NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
			{
				nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
				nk_layout_row_push(ctx, 500);
				nk_checkbox_label(ctx, "Single Step Mode", &flags->singleStepMode);

				if (flags->singleStepMode)
				{
					// The processor should only execute one operation at a time
					if (nk_button_label(ctx, "Step"))
					{
						cpu_run(system->cpu, system->memory);
					}
				}

				// Display the debug information
				nk_layout_row_static(ctx, 50, 200, 2);
				nk_label(ctx, "Current PC: ", NK_TEXT_CENTERED);
				nk_label(ctx, cpu_register_to_string(system->cpu->state->pc), NK_TEXT_LEFT);

				nk_layout_row_static(ctx, 300, 500, 2);
				if (nk_group_begin(ctx, "List", 0))
				{
					nk_layout_row_static(ctx, 25, 450, 1);
					nk_label(ctx, "CPU GPRs", NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "r0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->r0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "at", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->at), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "v0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->v0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "v1", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->v1), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "a0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->a0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "a1", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->a1), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "a2", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->a2), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "a3", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->a3), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t1", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t1), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t2", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t2), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t3", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t3), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t4", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t4), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t5", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t5), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t6", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t6), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t7", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t7), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s1", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s1), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s2", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s2), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s3", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s3), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s4", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s4), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s5", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s5), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s6", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s6), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s7", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s7), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t8", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t8), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "t9", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->t9), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "k0", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->k0), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "k1", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->k1), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "gp", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->gp), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "sp", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->sp), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "s8", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->s8), NK_TEXT_CENTERED);
					nk_layout_row_static(ctx, 18, 200, 2);
					nk_label(ctx, "ra", NK_TEXT_CENTERED);
					nk_label(ctx, cpu_register_to_string(system->cpu->state->ra), NK_TEXT_CENTERED);
				}
				nk_group_end(ctx);
			}
			nk_end(ctx);
		}

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
	flags_destroy(flags);

	nk_glfw3_shutdown();
	glfwTerminate();
	return 0;
}
