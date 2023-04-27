#include "DieCommand.h"
#include "HealthComponent.h"
#include "GameObject.h"

dae::DieCommand::DieCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
	pHealthComp = pGameObject->GetComponent<HealthComponent>();
}

void dae::DieCommand::Execute()
{
	pHealthComp->Die();
}
