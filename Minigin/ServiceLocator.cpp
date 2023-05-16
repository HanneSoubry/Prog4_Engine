#include "ServiceLocator.h"

using namespace dae;

SoundSystem* ServiceLocator::GetSoundSystem()
{
	if (m_pSoundSystem != nullptr) 
		return m_pSoundSystem.get();
	
	if (m_pDefaultSoundSystem == nullptr)
	{
		m_pDefaultSoundSystem.reset(new NullSoundSystem());
	}

	return m_pDefaultSoundSystem.get();
}

void ServiceLocator::RegisterSoundSystem(std::shared_ptr<SoundSystem> soundSystem)
{
	if (soundSystem == nullptr) 
		m_pSoundSystem = m_pDefaultSoundSystem;

	else m_pSoundSystem = soundSystem;
}