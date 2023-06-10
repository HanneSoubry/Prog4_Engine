#include "RenderTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Renderer.h"

dae::RenderTextComponent::RenderTextComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::RenderTextComponent::Render() const
{
	if (m_pTextComponent == nullptr)
		return;	// safety check

	std::shared_ptr<Texture2D> texture = m_pTextComponent->GetTexture();
	Transform transform = GetOwner()->GetTransform();

	Renderer::GetInstance().RenderTexture(*texture.get(), transform.GetPosition().x, transform.GetPosition().y);
}

void dae::RenderTextComponent::SetTextToRender(TextComponent* textComp)
{
	m_pTextComponent = textComp;
}
