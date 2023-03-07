#include "RenderTextureComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"

dae::RenderTextureComponent::RenderTextureComponent(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::RenderTextureComponent::Render() const
{
	if (m_pTextureComponent == nullptr)
		return;	// safety check

	std::shared_ptr<Texture2D> texture = m_pTextureComponent->GetTexture();
	Transform transform = GetOwner()->GetTransform();

	Renderer::GetInstance().RenderTexture(*texture.get(), transform.GetPosition().x, transform.GetPosition().y);
}

void dae::RenderTextureComponent::SetTextureToRender(std::shared_ptr<TextureComponent> textureComp)
{
	m_pTextureComponent = textureComp;
}
