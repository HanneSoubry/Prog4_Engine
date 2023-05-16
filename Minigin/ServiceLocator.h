#pragma once
#include "SoundSystemInterface.h"
#include <memory>

namespace dae
{
	class ServiceLocator final
	{
	public:
		// Sound
		static SoundSystem* GetSoundSystem();
		static void RegisterSoundSystem(std::shared_ptr<SoundSystem> soundSystem);

	private:
		// Sound
		static std::shared_ptr<SoundSystem> m_pSoundSystem;
		static std::shared_ptr<SoundSystem> m_pDefaultSoundSystem;
	};
}