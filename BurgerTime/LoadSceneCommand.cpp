#include "LoadSceneCommand.h"

dae::LoadSceneCommand::LoadSceneCommand(const std::string& levelFile, LevelLoaderComponent* levelLoader)
	: m_LevelFile(levelFile), m_LevelLoader(levelLoader)
{
}

void dae::LoadSceneCommand::Execute()
{
	m_LevelLoader->LoadLevelFromFile(m_LevelFile);
}
