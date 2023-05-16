#include "SdlSoundSystem.h"
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>

using namespace dae;

class SdlSoundSystem::SdlSoundSystemImpl
{
public:
	SdlSoundSystemImpl()
	{
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
		{
			std::cout << "Error in OpenAudio: " << Mix_GetError() << "\n";
		}
	}

	void Play(const std::string& soundPath, const float /*volume*/)
	{
		if (!m_pSounds.contains(soundPath))
		{
			// sound not loaded yet
			std::cout << "Loading sound " << soundPath << " in Play()\n";
			LoadSound(soundPath);
		}

		Mix_Chunk* sound = (*m_pSounds.find(soundPath)).second;

		if (sound != nullptr)
		{
			Mix_PlayChannel(-1, sound, 1);
		}
	}

	void LoadSound(const std::string& filePath)
	{
		if (m_pSounds.contains(filePath))
			return;	// sound already loaded

		// else load sound
		// TODO: load on other tread
		Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
		if(sound == nullptr)
		{
			std::cout << "Error when loading sound " << filePath << "\n";
			return;
		}

		m_pSounds[filePath] = sound;
	}

	void LoadSounds(const std::vector<std::string>& filePaths)
	{
		for (int i{}; i < static_cast<int>(filePaths.size()); ++i)
		{
			LoadSound(filePaths[i]);
		}
	}
private: 
	std::unordered_map<std::string, Mix_Chunk*> m_pSounds{};
};

dae::SdlSoundSystem::SdlSoundSystem()
{
	pImpl = new SdlSoundSystemImpl();
}

dae::SdlSoundSystem::~SdlSoundSystem()
{
	delete pImpl;
}

void SdlSoundSystem::Play(const std::string& soundPath, const float volume)
{
	pImpl->Play(soundPath, volume);
}

void dae::SdlSoundSystem::LoadSound(const std::string& filePath)
{
	pImpl->LoadSound(filePath);
}

void dae::SdlSoundSystem::LoadSounds(const std::vector<std::string>& filePaths)
{
	pImpl->LoadSounds(filePaths);
}
