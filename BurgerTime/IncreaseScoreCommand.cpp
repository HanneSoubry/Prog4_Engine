#include "IncreaseScoreCommand.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::IncreaseScoreCommand::IncreaseScoreCommand(GameObject* pGameObject, int pointIncrease)
	:Command(pGameObject), m_pointIncrease{pointIncrease}
{
	pScoreComp = pGameObject->GetComponent<ScoreComponent>();
}

void dae::IncreaseScoreCommand::Execute()
{
	pScoreComp->IncreaseScore(m_pointIncrease);
}
