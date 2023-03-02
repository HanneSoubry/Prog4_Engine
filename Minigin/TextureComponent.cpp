#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject> pParent)
	:BaseComponent(pParent)
{
}

void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

std::shared_ptr<dae::Texture2D>  dae::TextureComponent::GetTexture()
{
	return m_pTexture;
}
