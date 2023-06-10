#pragma once
#include "BaseEvent.h"
#include <string>

namespace dae
{
	class EventLoadSound : public Event
	{
	public:
		EventLoadSound(const std::string& soundPath) : m_SoundPath(soundPath) {}
		const std::string m_SoundPath{};
	};

	class EventLoadMusic : public Event
	{
	public:
		EventLoadMusic(const std::string& musicPath) : m_MusicPath(musicPath) {}
		const std::string m_MusicPath{};
	};

	class EventPlaySound : public Event
	{
	public:
		EventPlaySound(const std::string& soundPath, int volume, int loops) 
			: m_SoundPath(soundPath), m_Volume(volume), m_Loops(loops) {}
		const std::string m_SoundPath{};
		const int m_Volume{};
		const int m_Loops{};
	};

	class EventPlayMusic : public Event
	{
	public:
		EventPlayMusic(const std::string& musicPath, int volume, bool looping)
			: m_MusicPath(musicPath), m_Volume(volume), m_Looping(looping) {}
		const std::string m_MusicPath{};
		const int m_Volume{};
		const bool m_Looping{};
	};

	class EventQuitSound : public Event
	{
	public:
		explicit EventQuitSound() = default;
		// no data
	};
}