#include "sdk.h"

#include "img_rubik.h"
#include "img_logo.h"

#include <stdio.h>

#include <stb_image.h>

#define RGFWDEF
#include <RGFW.h>
#include <imgui_impl_rgfw.h>
#include <imgui_impl_opengl2.h>

#include <gf_version.h>

RGFW_window* win;
ImGuiIO*     io;
bool opengl;

void sdk_ui_scene(void) {
	int    open_about = 0;
	ImVec2 pos;
	ImVec2 menu;

	if(ImGui::BeginMainMenuBar()) {
		if(ImGui::BeginMenu("File")) {
			if(ImGui::MenuItem("New")) {
				scene = SDK_UI_PROJECT;
			}
			ImGui::Separator();
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

	opengl = true;
	if(scene == SDK_UI_INIT) {
		opengl_area.x = 0;
		opengl_area.y = menu.y;
		opengl_area.w = win->r.w;
		opengl_area.h = win->r.h - menu.y;
	} else if(scene == SDK_UI_PROJECT) {
		opengl = false;
		opengl_area.x = 200;
		opengl_area.y = menu.y;
		opengl_area.w = win->r.w - opengl_area.x;
		opengl_area.h = win->r.h - menu.y - 100;

		ImGui::SetNextWindowPos(ImVec2(0, menu.y));
		ImGui::SetNextWindowSize(ImVec2(opengl_area.x, win->r.h - menu.y));
		ImGui::Begin("Navigation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		if(ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_DefaultOpen)){
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(opengl_area.x, menu.y + opengl_area.h));
		ImGui::SetNextWindowSize(ImVec2(win->r.w - opengl_area.x, win->r.h - opengl_area.h - menu.y));
		ImGui::Begin("Stuff", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		ImGui::End();
	}

	if(open_about) {
		ImGui::OpenPopup("###About");
	}

	pos = ImVec2(win->r.w / 2 - 485 / 2, win->r.h / 2 - 300 / 2);
	ImGui::SetNextWindowPos(pos);
	ImGui::SetNextWindowSize(ImVec2(485, 300));
	if(ImGui::BeginPopupModal("About GoldFish SDK###About", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		pos = ImGui::GetContentRegionMax();

		pos.x -= 75;
		pos.y -= 25;

		ImGui::SetCursorPos(pos);
		if(ImGui::Button("OK", ImVec2(75, 25))) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::SetCursorPos(ImGui::GetCursorStartPos());
		if(ImGui::BeginTabBar("AboutTabBar")) {
			if(ImGui::BeginTabItem("GoldFish SDK###AboutGoldFishSDK")) {
				char	     buf[512];
				gf_version_t ver;

				gf_version_get(&ver);

				sprintf(buf, "Engine version %s", ver.full);

				ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x / 2 - 128 / 2);
				ImGui::Image((ImTextureID)(intptr_t)logo, ImVec2(128, 128));

				ImGui::Text(buf);

				ImGui::Text("Copyright (c) 2025");
				ImGui::SameLine();
				ImGui::TextLinkOpenURL("Pyrite Development Team", "https://github.com/pyrite-dev");

				ImGui::NewLine();
				ImGui::TextLinkOpenURL("https://github.com/pyrite-dev/goldfish-sdk");
				ImGui::EndTabItem();
			}

			if(ImGui::BeginTabItem("Contact###AboutGoldFishContact")) {
				if(ImGui::BeginTable("ContactTable", 2, ImGuiTableFlags_Borders)) {
					ImGui::TableSetupColumn("Platform");
					ImGui::TableSetupColumn("Location");
					ImGui::TableHeadersRow();

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("Discord");
					ImGui::TableNextColumn();
					ImGui::TextLinkOpenURL("https://discord.gg/yHWZVwu2Ta");

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("IRC");
					ImGui::TableNextColumn();
					ImGui::Text("#nishbox at");
					ImGui::SameLine();
					ImGui::TextLinkOpenURL("irc.nishi.boats", "ircs://irc.nishi.boats:6697");

					ImGui::EndTable();
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

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
	scene++;

	win = RGFW_createWindow("GoldFish SDK", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter);
	RGFW_window_makeCurrent(win);
	RGFW_window_swapInterval(win, 1);
	win->exitKey = RGFW_keyNULL;

	img = stbi_load_from_memory(img_rubik, img_rubik_len, &iw, &ih, &ic, 4);
	if(img != NULL) {
		glGenTextures(1, &cube);
		glBindTexture(GL_TEXTURE_2D, cube);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iw, ih, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(img);
	}

	img = stbi_load_from_memory(img_logo, img_logo_len, &iw, &ih, &ic, 4);
	if(img != NULL) {
		glGenTextures(1, &logo);
		glBindTexture(GL_TEXTURE_2D, logo);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iw, ih, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		RGFW_window_setIcon(win, img, RGFW_AREA(iw, ih), 4);

		stbi_image_free(img);
	}

	ImGui::CreateContext();
	io		= &ImGui::GetIO();
	io->DeltaTime	= 1.0 / 60.0;
	io->IniFilename = NULL;
	io->LogFilename = NULL;

	io->Fonts->GetTexDataAsRGBA32(&px, &tw, &th);

	ImGui_ImplRgfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();

	io->DisplayFramebufferScale = ImVec2(1, 1);
}

void sdk_ui_loop(void) {
	int calc = 0;
	double delta = io->DeltaTime;
	while(!RGFW_window_shouldClose(win)) {
		char title[512];
		ImDrawData* data;

		sprintf(title, "GoldFish SDK (%.1f FPS)", 1.0 / delta);

		RGFW_window_setName(win, title);

		RGFW_window_checkEvents(win, RGFW_eventNoWait);
		io->DisplaySize = ImVec2(win->r.w, win->r.h);

		ImGui::NewFrame();
		ImGui_ImplRgfw_NewFrame();
		ImGui_ImplOpenGL2_NewFrame();

		sdk_ui_scene();

		glViewport(0, 0, win->r.w, win->r.h);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		if(opengl){
			glEnable(GL_SCISSOR_TEST);
			glViewport(opengl_area.x, win->r.h - opengl_area.y - opengl_area.h, opengl_area.w, opengl_area.h);
			glScissor(opengl_area.x, win->r.h - opengl_area.y - opengl_area.h, opengl_area.w, opengl_area.h);
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
			sdk_opengl_render();
	
			glDisable(GL_SCISSOR_TEST);
	
			glViewport(0, 0, win->r.w, win->r.h);
		}
		ImGui::Render();
		data = ImGui::GetDrawData();
		ImGui_ImplOpenGL2_RenderDrawData(data);

		RGFW_window_swapBuffers(win);

		calc++;
		if(calc == 60){
			delta = io->DeltaTime;
			calc = 0;
		}
	}
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplRgfw_Shutdown();
	ImGui::DestroyContext();
}
}
