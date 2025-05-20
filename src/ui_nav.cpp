#include "sdk.h"

#include "imgui_include.h"

void nav(void) {
	double s = win->r.h - menu.y - 250 - 35;
	double b = 0;
	ImVec2 sz;

	ImGui::SetNextWindowPos(ImVec2(0, menu.y + 250));
	ImGui::SetNextWindowSize(ImVec2(opengl_area.x, s));
	ImGui::Begin("Navigation", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	if(ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::TreePop();
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(0, menu.y + 250 + s));
	ImGui::SetNextWindowSize(ImVec2(opengl_area.x, 35));
	ImGui::Begin("NavigationButton", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	sz   = ImGui::GetContentRegionAvail();
	b    = (opengl_area.x - sz.x) / 2;
	sz.x = (sz.x - b) / 2;
	if(ImGui::Button("Add", sz)) {
		open_file = 1;
	}
	ImGui::SameLine();
	ImGui::Button("Remove", sz);
	ImGui::End();
}
