#include "DieCommand.h"
#include "HealthComponent.h"
#include "GameObject.h"

dae::DieCommand::DieCommand(GameObject* pGameObject)
	: m_pGameObject(pGameObject)
{
	m_pHealthComp = pGameObject->GetComponent<HealthComponent>();
}

void dae::DieCommand::Execute()
{
	m_pHealthComp->Die();
}
