#include "SwitchGameCommand.h"

dae::SwitchGameCommand::SwitchGameCommand(GameManagerComponent* gameManager)
	: m_GameManager(gameManager)
{
}

void dae::SwitchGameCommand::Execute()
{
	m_GameManager->SwitchGame();
}
