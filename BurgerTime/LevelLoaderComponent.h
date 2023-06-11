#pragma once
#include "BaseComponent.h"
#include "LevelTextureComponent.h"
#include "LevelPropertiesComponent.h"
#include <string>
#include <vector>

namespace dae
{
	class LevelLoaderComponent final : public BaseComponent
	{
	public:
		LevelLoaderComponent(GameObject* pOwner);
		virtual ~LevelLoaderComponent() override = default;
		LevelLoaderComponent(const LevelLoaderComponent& other) = delete;
		LevelLoaderComponent(LevelLoaderComponent&& other) = delete;
		LevelLoaderComponent& operator=(const LevelLoaderComponent& other) = delete;
		LevelLoaderComponent& operator=(LevelLoaderComponent&& other) = delete;

		void LoadLevelFromFile(const std::string& levelFile);
		void SetLevelTexture(LevelTextureComponent* pTextureComp) { m_pLevelTexture = pTextureComp; }
		void SetLevelProperties(LevelPropertiesComponent* pPropertiesComp) { m_pLevelProperties = pPropertiesComp; }

		void SetLevelOffset(int x, int y);

	private:
		LevelTextureComponent* m_pLevelTexture{};
		LevelPropertiesComponent* m_pLevelProperties{};

		std::vector<std::shared_ptr<Texture2D>> m_pTextures{};
		std::vector<LevelTileProperties> m_Properties{};
	};

}