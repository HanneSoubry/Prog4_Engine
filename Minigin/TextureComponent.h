#pragma once
#include "BaseComponent.h"
#include <string>
#include <glm/glm.hpp>

namespace dae
{
	class Texture2D;

	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(GameObject* pOwner);
		virtual ~TextureComponent() override = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::string& fileName);
		std::shared_ptr<Texture2D> GetTexture();
		glm::vec2 GetSize();

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
