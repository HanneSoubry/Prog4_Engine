#pragma once

#include "Command.h"
#include <memory>
#include <string>

namespace dae
{
	class GameObject;

	class TestSoundCommand final : public Command
	{
	public:
		TestSoundCommand(GameObject* pGameObject);
		~TestSoundCommand() = default;

		TestSoundCommand(const TestSoundCommand& other) = delete;
		TestSoundCommand(TestSoundCommand&& other) = delete;
		TestSoundCommand& operator=(const TestSoundCommand& other) = delete;
		TestSoundCommand& operator=(TestSoundCommand&& other) = delete;

		virtual void Execute() override;

	private:
		std::string soundPath = "../Data/SfxJump.wav";
	};

}