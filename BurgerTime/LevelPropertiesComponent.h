#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
	struct LevelTileProperties
	{
		bool moveHorizontal{};
		bool moveVertical{};
	};

	class LevelPropertiesComponent : public BaseComponent
	{
	public:
		// needed for movement
		// should be set when creating/changing the level
		static void SetCurrentLevelMap(LevelPropertiesComponent* map) { m_pCurrentLevelMap = map; }
		static LevelPropertiesComponent* GetCurrentLevelMap() { return m_pCurrentLevelMap; }

		LevelPropertiesComponent(GameObject* pOwner);
		virtual ~LevelPropertiesComponent() override = default;
		LevelPropertiesComponent(const LevelPropertiesComponent& other) = delete;
		LevelPropertiesComponent(LevelPropertiesComponent&& other) = delete;
		LevelPropertiesComponent& operator=(const LevelPropertiesComponent& other) = delete;
		LevelPropertiesComponent& operator=(LevelPropertiesComponent&& other) = delete;

		glm::vec2 MoveOnGrid(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float speed);

		void SetLevelOffset(int x, int y) { m_LevelOffset = { x, y }; }
		void SetTileAmount(int x, int y);
		void SetTileSize(int x, int y);

		std::vector<std::vector<LevelTileProperties>>& GetPropertiesVector() { return m_pTiles; }

	private:
		glm::vec2 m_LevelOffset{};
		glm::vec2 m_LevelTotalSize{};
		glm::vec2 m_TileAmount{};
		glm::vec2 m_TileSize{32, 16};
		float m_CanWalkMargin{ 5 };
		float m_GroundMargin{ 1 };
		std::vector<std::vector<LevelTileProperties>> m_pTiles{};

		static LevelPropertiesComponent* m_pCurrentLevelMap;
	};
}


