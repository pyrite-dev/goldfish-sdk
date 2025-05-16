#include "sdk.h"

#define RGFWDEF
#include <RGFW.h>
#include <imgui_impl_rgfw.h>
#include <imgui_impl_opengl2.h>

#include <GL/gl.h>

RGFW_window* win;
ImGuiIO*     io;

enum SDK_UI_SCENE {
	SDK_UI_INIT = 0
};

int scene;

void sdk_ui_scene(void) {
	int open_about = 0;

	if(ImGui::BeginMainMenuBar()) {
		if(ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("Quit")) {
			}
			ImGui::EndMenu();
		}

		if(ImGui::BeginMenu("Edit")) {
			ImGui::EndMenu();
		}

		if(ImGui::BeginMenu("View")) {
			ImGui::EndMenu();
		}

		if(ImGui::BeginMenu("Help")) {
			if(ImGui::MenuItem("About")) {
				open_about = 1;
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if(scene == SDK_UI_INIT) {
	}

	if(open_about) {
		ImVec2 sz  = ImVec2(400, 200);
		ImVec2 pos = ImVec2(win->r.w / 2 - sz.x / 2, win->r.h / 2 - sz.y / 2);

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(sz);
		ImGui::OpenPopup("###About");
	}
	if(ImGui::BeginPopupModal("About GoldFish SDK###About", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		ImGui::EndPopup();
	}
}

extern "C" {
void sdk_ui_init(void) {
	unsigned char* px;
	int	       tw, th;

	scene = SDK_UI_INIT;

	win = RGFW_createWindow("GoldFish SDK", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter);
	RGFW_window_makeCurrent(win);
	win->exitKey = RGFW_keyNULL;

	ImGui::CreateContext();
	io	      = &ImGui::GetIO();
	io->DeltaTime = 1.0 / 60.0;

	io->Fonts->GetTexDataAsRGBA32(&px, &tw, &th);

	ImGui_ImplRgfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();

	io->DisplayFramebufferScale = ImVec2(1, 1);
}
void sdk_ui_loop(void) {
	while(!RGFW_window_shouldClose(win)) {
		ImDrawData* data;

		RGFW_window_checkEvents(win, RGFW_eventNoWait);
		io->DisplaySize = ImVec2(win->r.w, win->r.h);

		ImGui::NewFrame();
		ImGui_ImplRgfw_NewFrame();
		ImGui_ImplOpenGL2_NewFrame();

		sdk_ui_scene();

		glViewport(0, 0, win->r.w, win->r.h);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, win->r.w, win->r.h);
		ImGui::Render();
		data = ImGui::GetDrawData();
		ImGui_ImplOpenGL2_RenderDrawData(data);

		RGFW_window_swapBuffers(win);
	}
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplRgfw_Shutdown();
	ImGui::DestroyContext();
	RGFW_window_close(win);
}
}
