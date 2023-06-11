#pragma once
#include <memory>
#include "GameObject.h"
#include "LevelLoaderComponent.h"
#include "RenderLevelTilesComponent.h"
#include "InputManager.h"
#include "LoadSceneCommand.h"
#include "LevelPropertiesComponent.h"
#include "TextureComponent.h"
#include "RenderTextureComponent.h"
#include "MoveOnGridCommand.h"

namespace dae
{
	class LevelPrefab final
	{
	public:
		static std::unique_ptr<GameObject> Create(int levelOffsetX, int levelOffsetY, bool loadImmediately, std::string levelFile, bool addReloadCommand, SDL_Scancode button = SDL_SCANCODE_0)
		{
			auto level = std::make_unique<GameObject>();

			auto levelLoader = level->AddComponent<LevelLoaderComponent>(level.get());
			auto levelTexture = level->AddComponent<LevelTextureComponent>(level.get());
			auto levelProperties = level->AddComponent<LevelPropertiesComponent>(level.get());
			auto levelRenderer = level->AddComponent<RenderLevelTilesComponent>(level.get());

			levelLoader->SetLevelTexture(levelTexture);
			levelLoader->SetLevelProperties(levelProperties);
			levelRenderer->SetLevelTexture(levelTexture);

			levelLoader->SetLevelOffset(levelOffsetX, levelOffsetY);
			
			if(loadImmediately)
				levelLoader->LoadLevelFromFile(levelFile);

			if(addReloadCommand)
				InputManager::GetInstance().BindCommand(button, InputManager::InputAction::Up, std::make_unique<LoadSceneCommand>(levelFile, levelLoader));

			return std::move(level);
		}
	};

	class PlayerPrefab final
	{
	public:
		static std::unique_ptr<GameObject> Create(const std::string& texture, const glm::vec2& startPosition, float moveSpeed, const std::vector<unsigned int>& moveKeys, int& outInputId, int controllerId = -1)
		{
			glm::vec2 size{};
			auto player = BasePlayer(texture, startPosition, size);

			std::unique_ptr<Command<glm::vec2>> command{ std::move(std::make_unique<MoveOnGridCommand>(MoveOnGridCommand{player.get(), moveSpeed, size})) };
			outInputId = InputManager::GetInstance().BindCommand(moveKeys, InputManager::InputAction::Digital2DAxis,
				std::move(command), controllerId);

			return std::move(player);
		}

		static std::unique_ptr<GameObject> Create(const std::string& texture, const glm::vec2& startPosition, float moveSpeed, unsigned int moveKey, int& outInputId, int controllerId)
		{
			glm::vec2 size{};
			auto player = BasePlayer(texture, startPosition, size);

			std::unique_ptr<Command<glm::vec2>> command{ std::move(std::make_unique<MoveOnGridCommand>(MoveOnGridCommand{ player.get(), moveSpeed, size })) };
			outInputId = InputManager::GetInstance().BindCommand(moveKey, InputManager::InputAction::Digital2DAxis,
				std::move(command), controllerId);

			return std::move(player);
		}

	private: 
		static std::unique_ptr<GameObject> BasePlayer(const std::string& texture, const glm::vec2& startPosition, glm::vec2& outSize)
		{
			auto player = std::make_unique<GameObject>();
			player->SetPosition(startPosition.x, startPosition.y);

			// texture
			auto textureComp = player->AddComponent<TextureComponent>(player.get());
			textureComp->SetTexture(texture);
			auto renderTextureComp = player->AddComponent<RenderTextureComponent>(player.get());
			renderTextureComp->SetTextureToRender(textureComp);

			outSize = textureComp->GetSize();

			return std::move(player);
		}
	};
}