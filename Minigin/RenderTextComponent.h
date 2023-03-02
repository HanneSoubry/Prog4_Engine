#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;

	class RenderTextComponent final : public BaseComponent
	{
	public:
		RenderTextComponent(std::shared_ptr<GameObject> pParent);
		virtual ~RenderTextComponent() override = default;
		RenderTextComponent(const RenderTextComponent& other) = delete;
		RenderTextComponent(RenderTextComponent&& other) = delete;
		RenderTextComponent& operator=(const RenderTextComponent& other) = delete;
		RenderTextComponent& operator=(RenderTextComponent&& other) = delete;

		virtual void Render() const override;
	};
}
