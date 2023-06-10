#include "SdlSoundSystem.h"
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <deque>
#include "SoundEvents.h"
#include <mutex>

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

		m_LoadThread = std::jthread([&] {
			bool quit{ false };
			while (!quit)
			{
				std::unique_lock<std::mutex> lock{m_Mutex};
				// wait untill something is in the queue
				// lock will be released if waiting, and reaquired when passing the wait
				m_ConditionVariableLoad.wait(lock, [&] { return !m_LoadEvents.empty(); });

				// take first event
				std::shared_ptr<Event> event = m_LoadEvents.front();
				m_LoadEvents.pop_front();

				auto soundEvent{ dynamic_cast<EventLoadSound*>(event.get()) };
				if (soundEvent != nullptr)	// if load sound request
				{
					if (m_pSounds.contains(soundEvent->m_SoundPath))
						return;	// sound already loaded

					// release lock while doing the actual loading
					lock.unlock();

					// load new sound
					Mix_Chunk* sound = Mix_LoadWAV(soundEvent->m_SoundPath.c_str());
					if (sound == nullptr)
					{
						std::cout << "Error when loading sound " << soundEvent->m_SoundPath << "\n";
						return;
					}

					// re-lock
					lock.lock();
					m_pSounds[soundEvent->m_SoundPath] = sound;

					continue; // lock goes out of scope -> unlocked
				}

				auto musicEvent = dynamic_cast<EventLoadMusic*>(event.get());
				if (musicEvent != nullptr)	// if load music request
				{
					if (m_pMusics.contains(musicEvent->m_MusicPath))
						return;	// music already loaded

					// release lock while doing the actual loading
					lock.unlock();

					// load new music
					Mix_Music* music = Mix_LoadMUS(musicEvent->m_MusicPath.c_str());
					if (music == nullptr)
					{
						std::cout << "Error when loading music " << musicEvent->m_MusicPath << "\n";
						return;
					}

					// re-lock
					lock.lock();
					m_pMusics[musicEvent->m_MusicPath] = music;
					continue; //lock-out-of-scope-release
				}

				auto quitEvent{ dynamic_cast<EventQuitSound*>(event.get()) };
				if (quitEvent != nullptr)	// succesful cast
				{
					quit = true;
				}
		}});

		m_PlayThread = std::jthread([&] {
			bool quit{ false };
			while (!quit)
			{
				std::unique_lock<std::mutex> lock{m_Mutex};
				// wait untill something is in the queue
				// lock will be released if waiting, and reaquired when passing the wait
				m_ConditionVariablePlay.wait(lock, [&] { return !m_PlayEvents.empty(); });

				// take first event
				std::shared_ptr<Event> event = m_PlayEvents.front();
				m_PlayEvents.pop_front();

				auto soundEvent{ dynamic_cast<EventPlaySound*>(event.get()) };
				if (soundEvent != nullptr)	// if load sound request
				{
					if (!m_pSounds.contains(soundEvent->m_SoundPath))
					{
						// sound not loaded yet
						std::cout << "Loading sound " << soundEvent->m_SoundPath << " in Play()\n";
						LoadSound(soundEvent->m_SoundPath);

						m_ConditionVariablePlay.wait(lock, [&] { return m_pSounds.contains(soundEvent->m_SoundPath); });
					}

					Mix_Chunk* sound = (*m_pSounds.find(soundEvent->m_SoundPath)).second;

					// release lock
					lock.unlock();

					if (sound != nullptr)
					{
						Mix_VolumeChunk(sound, soundEvent->m_Volume);
						Mix_PlayChannel(-1, sound, soundEvent->m_Loops);
					}
					continue;
				}

				auto musicEvent{ dynamic_cast<EventPlayMusic*>(event.get()) };
				if (musicEvent != nullptr)	// if load sound request
				{
					if (!m_pMusics.contains(musicEvent->m_MusicPath))
					{
						// sound not loaded yet
						std::cout << "Loading music " << musicEvent->m_MusicPath << " in Play()\n";
						LoadMusic(musicEvent->m_MusicPath);

						m_ConditionVariablePlay.wait(lock, [&] { return m_pMusics.contains(musicEvent->m_MusicPath); });
					}

					if (m_pActiveMusic != nullptr)
						Mix_HaltMusic();

					Mix_Music* music = (*m_pMusics.find(musicEvent->m_MusicPath)).second;
					m_pActiveMusic = music;

					// release lock
					lock.unlock();

					Mix_VolumeMusic(musicEvent->m_Volume);
					Mix_PlayMusic(music, musicEvent->m_Looping ? -1 : 1);				
					continue;
				}

				auto quitEvent{ dynamic_cast<EventQuitSound*>(event.get()) };
				if (quitEvent != nullptr)	// succesful cast
				{
					quit = true;
				}
		}});
	}

	~SdlSoundSystemImpl()
	{
		for (auto& sound : m_pSounds)
		{
			Mix_FreeChunk(sound.second);		
		}
		for (auto& music : m_pMusics)
		{
			Mix_FreeMusic(music.second);
		}

		std::unique_lock<std::mutex> lock{m_Mutex};
		std::shared_ptr<Event> event { new EventQuitSound() };
		m_LoadEvents.push_back(event);
		m_PlayEvents.push_back(event);
		//lock-out-of-scope-release
		
		//jthread-out-of-scope-join
	}

	virtual void PlaySound(const std::string& soundPath, const float volume, int loops)
	{
		std::shared_ptr<Event> event { new EventPlaySound(soundPath, RemapVolume(volume), loops) };

		std::unique_lock<std::mutex> lock{m_Mutex};
		m_PlayEvents.push_back(event);
		m_ConditionVariablePlay.notify_all();
		//lock-out-of-scope-release
	}
	virtual void StopAllSounds()
	{
		Mix_HaltChannel(-1);
	}

	virtual void PlayMusic(const std::string& musicPath, const float volume, bool looping)
	{
		std::shared_ptr<Event> event { new EventPlayMusic(musicPath, RemapVolume(volume), looping) };

		std::unique_lock<std::mutex> lock{m_Mutex};
		m_PlayEvents.push_back(event);
		m_ConditionVariablePlay.notify_all();
		//lock-out-of-scope-release
	}

	virtual void PauzeMusic() 
	{
		Mix_PauseMusic();
	}

	virtual void ResumeMusic()
	{
		Mix_ResumeMusic();
	}

	virtual void StopMusic() 
	{
		Mix_HaltMusic();
	}

	virtual bool IsMusicPlaying()
	{
		if (Mix_PlayingMusic() == 0)
		{
			return false;
		}
		else return true;
	}

	void LoadSound(const std::string& filePath)
	{
		std::shared_ptr<Event> event { new EventLoadSound(filePath) };

		std::unique_lock<std::mutex> lock{m_Mutex};
		m_LoadEvents.push_back(event);
		m_ConditionVariableLoad.notify_all();
		//lock-out-of-scope-release
	}

	void LoadSounds(const std::vector<std::string>& filePaths)
	{
		for (int i{}; i < static_cast<int>(filePaths.size()); ++i)
		{
			LoadSound(filePaths[i]);
		}
	}

	void LoadMusic(const std::string& filePath)
	{
		std::shared_ptr<Event> event { new EventLoadMusic(filePath) };

		std::unique_lock<std::mutex> lock{m_Mutex};
		m_LoadEvents.push_back(event);
		m_ConditionVariableLoad.notify_all();
		//lock-out-of-scope-release
	}

private: 
	std::unordered_map<std::string, Mix_Chunk*> m_pSounds{};
	std::unordered_map<std::string, Mix_Music*> m_pMusics{};
	Mix_Music* m_pActiveMusic{};

	std::jthread m_LoadThread{};
	std::jthread m_PlayThread{};
	std::deque<std::shared_ptr<Event>> m_LoadEvents{};
	std::deque<std::shared_ptr<Event>> m_PlayEvents{};
	std::mutex m_Mutex{};
	std::condition_variable m_ConditionVariableLoad{};
	std::condition_variable m_ConditionVariablePlay{};

	int RemapVolume(float value)
	{
		// remap from [0,1] to [0, max volume]
		return static_cast<int>(value * MIX_MAX_VOLUME);
	}
};

dae::SdlSoundSystem::SdlSoundSystem()
{
	pImpl = new SdlSoundSystemImpl();
}

dae::SdlSoundSystem::~SdlSoundSystem()
{
	delete pImpl;
}

void dae::SdlSoundSystem::LoadSound(const std::string& filePath)
{
	pImpl->LoadSound(filePath);
}

void dae::SdlSoundSystem::LoadSounds(const std::vector<std::string>& filePaths)
{
	pImpl->LoadSounds(filePaths);
}

void dae::SdlSoundSystem::LoadMusic(const std::string& filePath)
{
	pImpl->LoadMusic(filePath);
}

void dae::SdlSoundSystem::PlaySound(const std::string& soundPath, const float volume, int loops)
{
	pImpl->PlaySound(soundPath, volume, loops);
}

void dae::SdlSoundSystem::StopAllSounds()
{
	pImpl->StopAllSounds();
}

void dae::SdlSoundSystem::PlayMusic(const std::string& musicPath, const float volume, bool looping)
{
	pImpl->PlayMusic(musicPath, volume, looping);
}

void dae::SdlSoundSystem::PauzeMusic()
{
	pImpl->PauzeMusic();
}

void dae::SdlSoundSystem::ResumeMusic()
{
	pImpl->ResumeMusic();
}

void dae::SdlSoundSystem::StopMusic()
{
	pImpl->StopMusic();
}

bool dae::SdlSoundSystem::IsMusicPlaying()
{
	return pImpl->IsMusicPlaying();
}
