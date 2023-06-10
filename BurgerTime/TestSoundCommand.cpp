#include "TestSoundCommand.h"
#include "ServiceLocator.h"

dae::TestSoundCommand::TestSoundCommand(std::string soundPath)
	: m_SoundPath(soundPath)
{
}

void dae::TestSoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem()->PlaySound(m_SoundPath, 1, 0);
}
