#pragma once
#include "BaseComponent.h"
#include <string>
#include <SDL_ttf.h>

namespace dae
{
	class Texture2D;
	class Font;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pOwner);
		virtual ~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(SDL_Color color);

		std::shared_ptr<Texture2D> GetTexture();

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		std::shared_ptr<Font> m_pFont{};
		std::string m_Text{};
		SDL_Color m_Color{ 255, 255, 255 };	// default white

		// dirty flag pattern
		bool m_ShouldUpdate{};
	};
}
