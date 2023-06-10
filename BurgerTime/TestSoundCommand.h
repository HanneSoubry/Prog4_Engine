#pragma once

#include "Command.h"
#include <memory>
#include <string>

namespace dae
{
	class GameObject;

	class TestSoundCommand final : public BaseCommand
	{
	public:
		TestSoundCommand(std::string soundPath);
		~TestSoundCommand() = default;

		virtual void Execute() override;

	private:
		std::string m_SoundPath;
	};

}