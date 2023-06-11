#include "LevelTextureComponent.h"

dae::LevelTextureComponent::LevelTextureComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::LevelTextureComponent::SetTileAmount(int x, int y)
{
	m_TileAmount = { x, y };

	m_pTiles.clear();
	for (int i{}; i < y; ++i)
	{
		// clear textures, reserve the right capacity
		m_pTiles.push_back(std::vector<std::shared_ptr<Texture2D>>{});
		m_pTiles.back().reserve(x);
	}
}
