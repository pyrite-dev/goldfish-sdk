#include "sdk.h"

#include "imgui_include.h"

void toolbox(void) {
	ImGui::SetNextWindowPos(ImVec2(0, menu.y));
	ImGui::SetNextWindowSize(ImVec2(opengl_area.x, 250));
	ImGui::Begin("Toolbox", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetNextWindowSize(ImGui::GetContentRegionAvail());
	if(ImGui::BeginListBox("###Tools")) {
		int i;
		for(i = 0; tools[i] != NULL; i++) {
			bool selected = i == tool_select;
			if(ImGui::Selectable(tools[i], selected)) tool_select = i;
		}
		ImGui::EndListBox();
	}
	ImGui::End();
}
