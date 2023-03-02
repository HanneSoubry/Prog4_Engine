#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;

	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(std::shared_ptr<GameObject> pParent);
		virtual ~TextureComponent() override = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::string& fileName);
		std::shared_ptr<Texture2D> GetTexture();

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
