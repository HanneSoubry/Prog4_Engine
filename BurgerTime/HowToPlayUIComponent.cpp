#include "HowToPlayUIComponent.h"
#include <imgui.h>
#include "BurgerTimeEvents.h"

dae::HowToPlayUIComponent::HowToPlayUIComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::HowToPlayUIComponent::RenderImGui()
{
	ImGui::Begin("Controls");

	ImGui::Text("Player 1 - Chef Peter Pepper - Keyboard");
	ImGui::BulletText("WASD : move character");
	ImGui::BulletText("Press ENTER to start/stop the game");

	ImGui::Separator();

	//ImGui::Text("Player 2 - Mr Pickle - Controller");
	//ImGui::BulletText("Left thumbstick : move character");
	//ImGui::BulletText("Left shoulder : suicide");
	//ImGui::BulletText("Right shoulder : score points");

	ImGui::End();
}
