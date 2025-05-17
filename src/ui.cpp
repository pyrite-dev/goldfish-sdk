#include "sdk.h"

#include "rubik.h"

#include <stdio.h>

#include <stb_image.h>

#define RGFWDEF
#include <RGFW.h>
#include <imgui_impl_rgfw.h>
#include <imgui_impl_opengl2.h>

#include <gf_version.h>

RGFW_window* win;
ImGuiIO*     io;

void sdk_ui_scene(void) {
	int    open_about = 0;
	ImVec2 pos;
	ImVec2 menu;

	if(ImGui::BeginMainMenuBar()) {
		if(ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("Quit")) {
				RGFW_window_setShouldClose(win, 1);
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

		menu = ImGui::GetWindowSize();

		ImGui::EndMainMenuBar();
	}

	if(scene == SDK_UI_INIT) {
		opengl_area.x = 0;
		opengl_area.y = menu.y;
		opengl_area.w = win->r.w;
		opengl_area.h = win->r.h - menu.y;
	}

	if(open_about) {
		ImGui::OpenPopup("###About");
	}

	pos = ImVec2(win->r.w / 2 - 350 / 2, win->r.h / 2 - 150 / 2);
	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(ImVec2(350, 150));
	if(ImGui::BeginPopupModal("About GoldFish SDK###About", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		char	     buf[512];
		gf_version_t ver;

		gf_version_get(&ver);

		sprintf(buf, "Engine version %s", ver.full);

		pos = ImGui::GetContentRegionMax();

		pos.x -= 75;
		pos.y -= 25;

		ImGui::SetCursorPos(pos);
		if(ImGui::Button("OK", ImVec2(75, 25))) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::SetCursorPos(ImGui::GetCursorStartPos());
		ImGui::Text("GoldFish SDK");

		ImGui::Text(buf);

		ImGui::Text("Copyright (c) 2025");
		ImGui::SameLine();
		ImGui::TextLinkOpenURL("Pyrite Development Team", "https://github.com/pyrite-dev");

		ImGui::NewLine();
		ImGui::TextLinkOpenURL("https://github.com/pyrite-dev/goldfish-sdk");

		ImGui::EndPopup();
	}
}

extern "C" {
void sdk_ui_init(void) {
	unsigned char* px;
	int	       tw, th;

	unsigned char* img;
	int	       iw, ih, ic;

	scene = SDK_UI_INIT;

	win = RGFW_createWindow("GoldFish SDK", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter);
	RGFW_window_makeCurrent(win);
	win->exitKey = RGFW_keyNULL;

	img = stbi_load_from_memory(rubik, rubik_len, &iw, &ih, &ic, 4);
	if(img != NULL) {
		glGenTextures(1, &cube);
		glBindTexture(GL_TEXTURE_2D, cube);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iw, ih, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(img);
	}

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

		glEnable(GL_SCISSOR_TEST);
		glViewport(opengl_area.x, win->r.h - opengl_area.y - opengl_area.h, opengl_area.w, opengl_area.h);
		glScissor(opengl_area.x, win->r.h - opengl_area.y - opengl_area.h, opengl_area.w, opengl_area.h);
		glClearColor(0.1, 0.1, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sdk_opengl_render();

		glDisable(GL_SCISSOR_TEST);

		glViewport(0, 0, win->r.w, win->r.h);
		ImGui::Render();
		data = ImGui::GetDrawData();
		ImGui_ImplOpenGL2_RenderDrawData(data);

		RGFW_window_swapBuffers(win);
	}
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplRgfw_Shutdown();
	ImGui::DestroyContext();
}
}
