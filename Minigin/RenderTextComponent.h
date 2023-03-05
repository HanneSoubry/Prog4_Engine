#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TextComponent;

	class RenderTextComponent final : public BaseComponent
	{
	public:
		RenderTextComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~RenderTextComponent() override = default;
		RenderTextComponent(const RenderTextComponent& other) = delete;
		RenderTextComponent(RenderTextComponent&& other) = delete;
		RenderTextComponent& operator=(const RenderTextComponent& other) = delete;
		RenderTextComponent& operator=(RenderTextComponent&& other) = delete;

		virtual void Render() const override;
		void SetTextToRender(std::shared_ptr<TextComponent> textComp);

	private:
		std::shared_ptr<TextComponent> m_pTextComponent{ nullptr };
	};
}
