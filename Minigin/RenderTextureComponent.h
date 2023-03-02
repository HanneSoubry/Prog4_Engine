#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;

	class RenderTextureComponent final : public BaseComponent
	{
	public:
		RenderTextureComponent(std::shared_ptr<GameObject> pParent);
		virtual ~RenderTextureComponent() override = default;
		RenderTextureComponent(const RenderTextureComponent& other) = delete;
		RenderTextureComponent(RenderTextureComponent&& other) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent& other) = delete;
		RenderTextureComponent& operator=(RenderTextureComponent&& other) = delete;

		virtual void Render() const override;
	};
}