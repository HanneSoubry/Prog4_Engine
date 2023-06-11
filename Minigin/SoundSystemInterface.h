#pragma once
#include <string>
#include <vector>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void PlaySound(const std::string& soundPath, const float volume, int loops) = 0;
		virtual void StopAllSounds() = 0;

		virtual void PlayMusic(const std::string& musicPath, const float volume, bool looping) = 0;
		virtual void PauzeMusic() = 0;
		virtual void ResumeMusic() = 0;
		virtual void StopMusic() = 0;
		virtual bool IsMusicPlaying() = 0;

		virtual void LoadSound(const std::string& filePath) = 0;
		virtual void LoadSounds(const std::vector<std::string>& filePaths) = 0;
		virtual void LoadMusic(const std::string& filePath) = 0;

		virtual void Mute(bool mute) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;

		virtual void PlaySound(const std::string& , const float , int ) {}
		virtual void StopAllSounds() {}

		virtual void PlayMusic(const std::string& , const float , bool ) {}
		virtual void PauzeMusic() {}
		virtual void ResumeMusic() {}
		virtual void StopMusic() {}
		virtual bool IsMusicPlaying() { return false; }

		virtual void LoadSound(const std::string&) override {}
		virtual void LoadSounds(const std::vector<std::string>&) override {}
		virtual void LoadMusic(const std::string& ) {}

		virtual void Mute(bool) {}
	};
}