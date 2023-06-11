#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class Scene;

	class GameManagerComponent final : public BaseComponent
	{
	public:
		GameManagerComponent(GameObject* pOwner);
		virtual ~GameManagerComponent() override = default;
		GameManagerComponent(const GameManagerComponent& other) = delete;
		GameManagerComponent(GameManagerComponent&& other) = delete;
		GameManagerComponent& operator=(const GameManagerComponent& other) = delete;
		GameManagerComponent& operator=(GameManagerComponent&& other) = delete;

		void SwitchGame();
		void SetScene(Scene* scene) { m_Scene = scene; }
		void Initialize();

	private:
		bool m_InGame{false};
		Scene* m_Scene{};
		std::vector<GameObject*> m_LevelObjects{};
		std::vector<int> m_PlayerInputs{};
	};
}
