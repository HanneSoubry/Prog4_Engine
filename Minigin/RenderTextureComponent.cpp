#include "RenderTextureComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Renderer.h"

dae::RenderTextureComponent::RenderTextureComponent(std::shared_ptr<GameObject> pParent)
	:BaseComponent(pParent)
{
}

void dae::RenderTextureComponent::Render() const
{
	std::shared_ptr<GameObject> parent{ m_pParent.lock() };
	std::shared_ptr<TextureComponent> textureComponent{ parent->GetComponent<TextureComponent>() };

	if (textureComponent == nullptr)
		return;	// safety check

	std::shared_ptr<Texture2D> texture = textureComponent->GetTexture();
	Transform transform = parent->GetPosition();

	Renderer::GetInstance().RenderTexture(*texture.get(), transform.GetPosition().x, transform.GetPosition().y);
}
