#pragma once
#include "SoundSystemInterface.h"
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class SdlSoundSystem final : public SoundSystem
	{
		class SdlSoundSystemImpl;
	public:
		SdlSoundSystem();
		~SdlSoundSystem();

		SdlSoundSystem(const SdlSoundSystem& other) = delete;
		SdlSoundSystem(SdlSoundSystem&& other) = delete;
		SdlSoundSystem& operator=(const SdlSoundSystem& other) = delete;
		SdlSoundSystem& operator=(SdlSoundSystem&& other) = delete;

		virtual void Play(const std::string& soundPath, const float volume) override;

		virtual void LoadSound(const std::string& filePath) override;
		virtual void LoadSounds(const std::vector<std::string>& filePaths) override;

	private:
		SdlSoundSystemImpl* pImpl;
	};
}