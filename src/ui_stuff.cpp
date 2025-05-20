#include "sdk.h"

#include "imgui_include.h"

void stuff(void) {
	ImGui::SetNextWindowPos(ImVec2(opengl_area.x, menu.y + opengl_area.h));
	ImGui::SetNextWindowSize(ImVec2(win->r.w - opengl_area.x, win->r.h - opengl_area.h - menu.y));
	ImGui::Begin("Stuff", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::End();
}
