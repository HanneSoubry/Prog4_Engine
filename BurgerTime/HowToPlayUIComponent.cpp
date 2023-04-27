#include "HowToPlayUIComponent.h"
#include <imgui.h>

dae::HowToPlayUIComponent::HowToPlayUIComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::HowToPlayUIComponent::RenderImGui()
{
	ImGui::Begin("Controls");

	ImGui::Text("Player 1 - Mr Hotdog - Keyboard");
	ImGui::BulletText("WASD : move character");
	ImGui::BulletText("E : suicide");
	ImGui::BulletText("Q : score points");

	ImGui::Separator();

	ImGui::Text("Player 2 - Mr Pickle - Controller");
	ImGui::BulletText("Left thumbstick : move character");
	ImGui::BulletText("Left shoulder : suicide");
	ImGui::BulletText("Right shoulder : score points");

	ImGui::End();
}
