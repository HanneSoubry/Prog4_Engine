#include "MoveCommand.h"
#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "LevelPropertiesComponent.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pGameObject, float speed)
	: m_pGameObject{ pGameObject },
	m_MovementSpeed{ speed }
{
}

void dae::MoveCommand::Execute(const glm::vec2& movementDirection)
{
	float elapsedSec = GameTime::GetInstance().ElapsedSeconds();
	
	glm::vec3 pos = m_pGameObject->GetTransform().GetPosition();
	pos.x += m_MovementSpeed * elapsedSec * movementDirection.x;
	// - y because top of the window is 0, bottom is window height value
	pos.y -= m_MovementSpeed * elapsedSec * movementDirection.y;
	
	m_pGameObject->SetPosition(pos.x, pos.y);
}

