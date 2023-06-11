#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include <vector>
#include "Texture2D.h"

namespace dae
{
	class LevelTextureComponent final : public BaseComponent
	{
	public:
		LevelTextureComponent(GameObject* pOwner);
		virtual ~LevelTextureComponent() override = default;
		LevelTextureComponent(const LevelTextureComponent& other) = delete;
		LevelTextureComponent(LevelTextureComponent&& other) = delete;
		LevelTextureComponent& operator=(const LevelTextureComponent& other) = delete;
		LevelTextureComponent& operator=(LevelTextureComponent&& other) = delete;

		void SetLevelOffset(int x, int y) { m_LevelOffset = { x, y }; }
		void SetTileAmount(int x, int y);
		void SetTileSize(int x, int y) { m_TileSize = { x, y }; }

		glm::vec2 GetLevelOffset() { return m_LevelOffset; }
		glm::vec2 GetTileAmount() { return m_TileAmount; }
		glm::vec2 GetTileSize() { return m_TileSize; }
		std::vector<std::vector<std::shared_ptr<Texture2D>>>& GetTextureVector() { return m_pTiles; }

	private:
		glm::vec2 m_LevelOffset{};
		glm::vec2 m_TileAmount{};
		glm::vec2 m_TileSize{16, 8};
		std::vector<std::vector<std::shared_ptr<Texture2D>>> m_pTiles{};
	};

}