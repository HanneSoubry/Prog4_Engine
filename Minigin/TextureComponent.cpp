#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
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

glm::vec2 dae::TextureComponent::GetSize()
{
	if (m_pTexture != nullptr)
	{
		return m_pTexture->GetSize();
	}
	else return { 0, 0 };
}
