#include "TestSoundCommand.h"
#include "ServiceLocator.h"

dae::TestSoundCommand::TestSoundCommand(std::string soundPath)
	: m_SoundPath(soundPath)
{
}

void dae::TestSoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem()->Play(m_SoundPath, 10);
}
