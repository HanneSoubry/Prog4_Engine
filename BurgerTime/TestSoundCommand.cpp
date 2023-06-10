#include "TestSoundCommand.h"
#include "ServiceLocator.h"

dae::TestSoundCommand::TestSoundCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
}

void dae::TestSoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem()->Play(soundPath, 10);
}
