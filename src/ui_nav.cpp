#include "sdk.h"

#include "imgui_include.h"

void nav(void) {
	double s = win->r.h - menu.y - 250;
	double b = 0;
	ImVec2 sz;

	ImGui::SetNextWindowPos(ImVec2(0, menu.y + 250));
	ImGui::SetNextWindowSize(ImVec2(opengl_area.x, s));
	ImGui::Begin("Navigation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::End();
}
