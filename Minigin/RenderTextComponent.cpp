#include "RenderTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Renderer.h"

dae::RenderTextComponent::RenderTextComponent(std::shared_ptr<GameObject> pParent)
	:BaseComponent(pParent)
{
}

void dae::RenderTextComponent::Render() const
{
	std::shared_ptr<GameObject> parent{ m_pParent.lock() };
	std::shared_ptr<TextComponent> textComponent{ parent->GetComponent<TextComponent>() };

	if (textComponent == nullptr)
		return;	// safety check

	std::shared_ptr<Texture2D> texture = textComponent->GetTexture();
	Transform transform = parent->GetPosition();

	Renderer::GetInstance().RenderTexture(*texture.get(), transform.GetPosition().x, transform.GetPosition().y);
}
