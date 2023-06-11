#include "MoveOnGridCommand.h"
#include "GameObject.h"
#include "LevelPropertiesComponent.h"

dae::MoveOnGridCommand::MoveOnGridCommand(GameObject* pGameObject, float speed, const glm::vec2& characterSize)
	: m_pGameObject(pGameObject), m_MovementSpeed(speed), m_Size(characterSize)
{
}

void dae::MoveOnGridCommand::Execute(const glm::vec2& movementDirection)
{
	auto& position = m_pGameObject->GetTransform().GetPosition();
	auto levelMap{ LevelPropertiesComponent::GetCurrentLevelMap() };

	if (levelMap != nullptr)
	{
		auto newPosition = levelMap->MoveOnGrid({ position.x, position.y }, m_Size, movementDirection, m_MovementSpeed);
		m_pGameObject->SetPosition(newPosition.x, newPosition.y);
	}
}
