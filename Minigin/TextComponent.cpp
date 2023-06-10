#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <stdexcept>

using namespace dae;

dae::TextComponent::TextComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_ShouldUpdate = true;

	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), m_Color);
	if (surf == nullptr) 
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = std::make_shared<Texture2D>(texture);
}

std::shared_ptr<Texture2D> dae::TextComponent::GetTexture()
{
	if (m_ShouldUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);

		m_ShouldUpdate = false;
	}

	return m_pTexture;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pFont = font;
	m_ShouldUpdate = true;
}

void dae::TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
	m_ShouldUpdate = true;
}
