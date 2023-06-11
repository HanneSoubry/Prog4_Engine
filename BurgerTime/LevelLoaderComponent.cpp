#include "LevelLoaderComponent.h"
#include "GameObject.h"
#include <iostream>
#include "ResourceManager.h"
#include <fstream>
#include <sstream>

dae::LevelLoaderComponent::LevelLoaderComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
	auto& resourceManager{ ResourceManager::GetInstance() };
	m_pTextures.push_back(nullptr);	// nothing, just background
	m_pTextures.push_back(resourceManager.LoadTexture("Level/PlatformDark.png"));
	m_pTextures.push_back(resourceManager.LoadTexture("Level/BottomStairsDark.png"));
	m_pTextures.push_back(resourceManager.LoadTexture("Level/BottomStairsLight.png"));
	m_pTextures.push_back(resourceManager.LoadTexture("Level/StairsWithPlatformDark.png"));
	m_pTextures.push_back(resourceManager.LoadTexture("Level/StairsWithPlatformLight.png"));
	m_pTextures.push_back(resourceManager.LoadTexture("Level/Stairs.png"));

	m_Properties.push_back({ false, false });
	m_Properties.push_back({ true,  false });	// only horizontal movement
	m_Properties.push_back({ true,  false });
	m_Properties.push_back({ true,  false });
	m_Properties.push_back({ true,  true });	// horizontal and vertical
	m_Properties.push_back({ true,  true });
	m_Properties.push_back({ false, true });	// only vertical movement
}

void dae::LevelLoaderComponent::LoadLevelFromFile(const std::string& levelFile)
{
	if (m_pLevelTexture == nullptr)
	{
		m_pLevelTexture = GetOwner()->GetComponent<LevelTextureComponent>();
		if (m_pLevelTexture == nullptr)
		{
			std::cout << "Level loader could not find the level texture component\n";
			return;
		}
	}

	if (m_pLevelProperties == nullptr)
	{
		m_pLevelProperties = GetOwner()->GetComponent<LevelPropertiesComponent>();
		if (m_pLevelProperties == nullptr)
		{
			std::cout << "Level loader could not find the level properties component\n";
			return;
		}
	}

	std::ifstream level{ levelFile };
	if (!level.is_open())
	{
		std::cout << "Failed to open level file\n";
		return;
	}

	// amount of tiles
	std::string nextLine{};
	std::getline(level, nextLine, 'x');
	int amountX{ std::stoi(nextLine) };
	std::getline(level, nextLine);
	int amountY{ std::stoi(nextLine) };
	++amountY;	// extra row
	m_pLevelTexture->SetTileAmount(amountX, amountY);
	m_pLevelProperties->SetTileAmount(amountX, amountY);

	auto size{ m_pTextures[1]->GetSize() };
	m_pLevelTexture->SetTileSize(size.x, size.y);
	m_pLevelProperties->SetTileSize(size.x, size.y);

	auto& textures{ m_pLevelTexture->GetTextureVector() };
	auto& properties{ m_pLevelProperties->GetPropertiesVector() };
	
	// textures & properties
	for (int y{}; y < amountY; ++y)
	{
		if (y == 0)
		{
			// add empty row at the top
			for (int x{}; x < amountX; ++x)
			{
				textures[y].emplace_back(m_pTextures[0]);
				properties[y].emplace_back(m_Properties[0]);
			}
		}
		else
		{
			std::getline(level, nextLine);
			for (int x{}; x < amountX; ++x)
			{
				std::string nextChar{nextLine[x]};
				int index{ std::stoi(nextChar) };
				textures[y].emplace_back(m_pTextures[index]);
				properties[y].emplace_back(m_Properties[index]);
			}
		}
	}

	LevelPropertiesComponent::SetCurrentLevelMap(m_pLevelProperties);
}

void dae::LevelLoaderComponent::UnloadCurrentLevel()
{
	m_pLevelProperties->SetTileAmount(0, 0);
	m_pLevelTexture->SetTileAmount(0, 0);
	LevelPropertiesComponent::SetCurrentLevelMap(nullptr);
}

void dae::LevelLoaderComponent::SetLevelOffset(int x, int y)
{
	m_pLevelProperties->SetLevelOffset(x, y);
	m_pLevelTexture->SetLevelOffset(x, y);
}
