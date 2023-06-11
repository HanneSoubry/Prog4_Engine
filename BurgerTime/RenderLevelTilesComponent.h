#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class LevelTextureComponent;

	class RenderLevelTilesComponent final : public BaseComponent
	{
	public:
		RenderLevelTilesComponent(GameObject* pOwner);
		virtual ~RenderLevelTilesComponent() override = default;
		RenderLevelTilesComponent(const RenderLevelTilesComponent& other) = delete;
		RenderLevelTilesComponent(RenderLevelTilesComponent&& other) = delete;
		RenderLevelTilesComponent& operator=(const RenderLevelTilesComponent& other) = delete;
		RenderLevelTilesComponent& operator=(RenderLevelTilesComponent&& other) = delete;

		virtual void Render() const override;
		void SetLevelTexture(LevelTextureComponent* textureComp);

	private:
		LevelTextureComponent* m_pTextureComponent{ nullptr };
	};
}