#include "MoveCommand.h"
#include "GameObject.h"
#include "Time.h"
#include "InputManager.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pGameObject, float speed)
	: Command(pGameObject), 
	m_MovementSpeed{ speed }
{
}

void dae::MoveCommand::Execute()
{
	float elapsedSec = Time::GetInstance().ElapsedSeconds();
	glm::vec2 input = InputManager::GetInstance().Get2DAxisValue();

	glm::vec3 pos = GetGameObject()->GetTransform().GetPosition();
	pos.x += m_MovementSpeed * elapsedSec * input.x;

	// - y because top of the window is 0, bottom is window height value
	pos.y -= m_MovementSpeed * elapsedSec * input.y;

	GetGameObject()->SetPosition(pos.x, pos.y);
}
