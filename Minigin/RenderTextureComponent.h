#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TextureComponent;

	class RenderTextureComponent final : public BaseComponent
	{
	public:
		RenderTextureComponent(GameObject* pOwner);
		virtual ~RenderTextureComponent() override = default;
		RenderTextureComponent(const RenderTextureComponent& other) = delete;
		RenderTextureComponent(RenderTextureComponent&& other) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent& other) = delete;
		RenderTextureComponent& operator=(RenderTextureComponent&& other) = delete;

		virtual void Render() const override;
		void SetTextureToRender(TextureComponent* textureComp);

	private: 
		TextureComponent* m_pTextureComponent{ nullptr };
	};
}