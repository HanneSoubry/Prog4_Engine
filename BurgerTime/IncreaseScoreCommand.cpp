#include "IncreaseScoreCommand.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::IncreaseScoreInputCommand::IncreaseScoreInputCommand(GameObject* pGameObject, int pointIncrease)
	:m_pGameObject(pGameObject), m_pointIncrease{pointIncrease}
{
	m_pScoreComp = pGameObject->GetComponent<ScoreComponent>();
}

void dae::IncreaseScoreInputCommand::Execute()
{
	m_pScoreComp->IncreaseScore(m_pointIncrease);
}
