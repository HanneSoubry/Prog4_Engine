#pragma once
#include "Command.h"
#include <string>
#include "LevelLoaderComponent.h"

namespace dae
{
	class LoadSceneCommand final : public BaseCommand
	{
	public:
		LoadSceneCommand(const std::string& levelFile, LevelLoaderComponent* levelLoader);
		~LoadSceneCommand() = default;

		virtual void Execute() override;

	private:
		std::string m_LevelFile{};
		LevelLoaderComponent* m_LevelLoader{};
	};

}