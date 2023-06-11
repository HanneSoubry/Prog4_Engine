#include "GameManagerComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "HowToPlayUIComponent.h"
#include "Prefabs.h"
#include "SwitchGameCommand.h"

dae::GameManagerComponent::GameManagerComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::GameManagerComponent::SwitchGame()
{
	for (auto object : m_LevelObjects)
	{
		object->RemoveGameObject();
	}
	m_LevelObjects.clear();
	for (auto input : m_PlayerInputs)
	{
		InputManager::GetInstance().RemoveCommand(input);
	}
	m_PlayerInputs.clear();

	if (m_InGame)
	{
		auto ui = m_Scene->Add(std::move(std::make_unique<GameObject>()));
		ui->AddComponent<HowToPlayUIComponent>(ui);
		m_LevelObjects.push_back(ui);
	}
	else
	{
		int levelPosX{ 120 };
		int levelPosY{ 90 };
		m_LevelObjects.push_back(m_Scene->Add(std::move(LevelPrefab::Create(levelPosX, levelPosY, true, "../Data/Level/Level1.txt", false))));

		std::vector<unsigned int> keys{ static_cast<unsigned int>(SDL_SCANCODE_A),
			static_cast<unsigned int>(SDL_SCANCODE_D),
			static_cast<unsigned int>(SDL_SCANCODE_W),
			static_cast<unsigned int>(SDL_SCANCODE_S) };

		int inputId{};
		m_LevelObjects.push_back(m_Scene->Add(std::move(PlayerPrefab::Create("ChefPeterPepper.png", { levelPosX, levelPosY - 16 }, 100, keys, inputId, -1))));
		m_PlayerInputs.push_back(inputId);
	}

	m_InGame = !m_InGame;
}

void dae::GameManagerComponent::Initialize()
{
	auto ui = m_Scene->Add(std::move(std::make_unique<GameObject>()));
	ui->AddComponent<HowToPlayUIComponent>(ui);
	m_LevelObjects.push_back(ui);

	std::unique_ptr<BaseCommand> command{ std::move(std::make_unique<SwitchGameCommand>(SwitchGameCommand{ this })) };
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_RETURN, InputManager::InputAction::Up,
		std::move(command), -1);
}
