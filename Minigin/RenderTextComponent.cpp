#include "RenderTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Renderer.h"

dae::RenderTextComponent::RenderTextComponent(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::RenderTextComponent::Render() const
{
	if (m_pTextComponent == nullptr)
		return;	// safety check

	std::shared_ptr<Texture2D> texture = m_pTextComponent->GetTexture();
	Transform transform = GetOwner()->GetPosition();

	Renderer::GetInstance().RenderTexture(*texture.get(), transform.GetPosition().x, transform.GetPosition().y);
}

void dae::RenderTextComponent::SetTextToRender(std::shared_ptr<TextComponent> textComp)
{
	m_pTextComponent = textComp;
}
