#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "TextComponent.h"
#include "RenderTextComponent.h"
#include "TextureComponent.h"
#include "RenderTextureComponent.h"
#include "FPSComponent.h"

void load()
{
	// scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);


	// Background
	auto go = std::make_shared<dae::GameObject>();
	scene.Add(go);

	go->SetPosition(0, 0);

	auto textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("background.tga");

	auto renderTextureComp = go->AddComponent<dae::RenderTextureComponent>(go);

	// Title
	go = std::make_shared<dae::GameObject>();
	scene.Add(go);

	go->SetPosition(80, 40);

	auto textComp = go->AddComponent<dae::TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");

	auto renderTextComp = go->AddComponent<dae::RenderTextComponent>(go);
	
	// Logo
	go = std::make_shared<dae::GameObject>();
	scene.Add(go);

	go->SetPosition(216, 180);

	textureComp = go->AddComponent<dae::TextureComponent>(go);
	textureComp->SetTexture("logo.tga");

	renderTextureComp = go->AddComponent<dae::RenderTextureComponent>(go);
	
	// FPS Counter
	go = std::make_shared<dae::GameObject>();
	scene.Add(go);

	go->SetPosition(2, 10);

	textComp = go->AddComponent<dae::TextComponent>(go);
	textComp->SetFont(fontFPS);
	textComp->SetColor({ 255, 255, 0 });
	textComp->SetText("-- FPS");

	renderTextComp = go->AddComponent<dae::RenderTextComponent>(go);

	auto fpsComp = go->AddComponent<dae::FPSComponent>(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}