#include "RenderLevelTilesComponent.h"
#include "LevelTextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderLevelTilesComponent::RenderLevelTilesComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::RenderLevelTilesComponent::Render() const
{
	const glm::vec2 tileAmount{m_pTextureComponent->GetTileAmount()};
	const glm::vec2 tileSize{m_pTextureComponent->GetTileSize()};
	const glm::vec2 levelOffset{m_pTextureComponent->GetLevelOffset()};
	auto& textures{ m_pTextureComponent->GetTextureVector() };

	glm::vec2 offset{levelOffset - tileSize};
	for (int y{}; y < tileAmount.y; ++y)
	{
		offset.y += tileSize.y;
		offset.x = levelOffset.x - tileSize.x;

		for (int x{}; x < tileAmount.x; ++x)
		{
			offset.x += tileSize.x;
			if (textures[y][x] == nullptr)
				continue;

			Renderer::GetInstance().RenderTexture(*textures[y][x].get(), offset.x, offset.y);
		}
	}
}

void dae::RenderLevelTilesComponent::SetLevelTexture(LevelTextureComponent* textureComp)
{
	m_pTextureComponent = textureComp;
}
