#pragma once
#include <string>
#include <vector>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void Play(const std::string& soundPath, const float volume) = 0;

		virtual void LoadSound(const std::string& filePath) = 0;
		virtual void LoadSounds(const std::vector<std::string>& filePaths) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;

		virtual void Play(const std::string&, const float) override { }

		virtual void LoadSound(const std::string&) override { }
		virtual void LoadSounds(const std::vector<std::string>&) override { }
	};
}