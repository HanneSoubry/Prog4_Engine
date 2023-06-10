#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TextComponent;

	class RenderTextComponent final : public BaseComponent
	{
	public:
		RenderTextComponent(GameObject* pOwner);
		virtual ~RenderTextComponent() override = default;
		RenderTextComponent(const RenderTextComponent& other) = delete;
		RenderTextComponent(RenderTextComponent&& other) = delete;
		RenderTextComponent& operator=(const RenderTextComponent& other) = delete;
		RenderTextComponent& operator=(RenderTextComponent&& other) = delete;

		virtual void Render() const override;
		void SetTextToRender(TextComponent* textComp);

	private:
		TextComponent* m_pTextComponent{ nullptr };
	};
}
