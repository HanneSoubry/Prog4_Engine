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

		virtual void PlaySound(const std::string& soundPath, const float volume, int loops) override;
		virtual void StopAllSounds() override;

		virtual void PlayMusic(const std::string& musicPath, const float volume, bool looping) override;
		virtual void PauzeMusic() override;
		virtual void ResumeMusic() override;
		virtual void StopMusic() override;
		virtual bool IsMusicPlaying() override;

		virtual void LoadSound(const std::string& filePath) override;
		virtual void LoadSounds(const std::vector<std::string>& filePaths) override;
		virtual void LoadMusic(const std::string& filePath) override;

		virtual void Mute(bool mute) override;

	private:
		SdlSoundSystemImpl* pImpl;
	};
}