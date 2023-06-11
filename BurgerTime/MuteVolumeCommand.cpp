#include "MuteVolumeCommand.h"
#include "ServiceLocator.h"

dae::MuteVolumeCommand::MuteVolumeCommand(bool isMusicPlaying)
	: m_IsMuted(!isMusicPlaying)
{
}

void dae::MuteVolumeCommand::Execute()
{
	auto ss = ServiceLocator::GetSoundSystem();

	m_IsMuted = !m_IsMuted;
	ss->Mute(m_IsMuted);
}
