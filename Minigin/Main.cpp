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
#include "RotatorComponent.h"


void load()
{
	using namespace dae;

	// scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);


	// Background
	auto go = std::make_shared<GameObject>();
	scene.Add(go);

	go->SetPosition(0, 0);

	auto textureComp = go->AddComponent<TextureComponent>(go);
	textureComp->SetTexture("background.tga");

	auto renderTextureComp = go->AddComponent<RenderTextureComponent>(go);
	renderTextureComp->SetTextureToRender(textureComp);

	// Title
	go = std::make_shared<GameObject>();
	scene.Add(go);

	go->SetPosition(80, 40);

	auto textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");

	auto renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);
	
	// Logo
	go = std::make_shared<GameObject>();
	scene.Add(go);

	go->SetPosition(216, 150);

	textureComp = go->AddComponent<TextureComponent>(go);
	textureComp->SetTexture("logo.tga");

	renderTextureComp = go->AddComponent<RenderTextureComponent>(go);
	renderTextureComp->SetTextureToRender(textureComp);
	
	// FPS Counter
	go = std::make_shared<GameObject>();
	scene.Add(go);

	go->SetPosition(2, 10);

	textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(fontFPS);
	textComp->SetColor({ 255, 255, 0 });
	textComp->SetText("-- FPS");

	renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);

	auto fpsComp = go->AddComponent<FPSComponent>(go);
	fpsComp->SetTextTarget(textComp);

	// Mr Hot Dog
	auto hotDog = std::make_shared<GameObject>();
	scene.Add(hotDog);

	auto rotComp = hotDog->AddComponent<RotatorComponent>(hotDog);
	rotComp->SetCenter(320, 280);
	rotComp->SetRadius(40);
	rotComp->SetSpeed(3);

	textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");

	renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);

	// Mr Pickle
	auto pickle = std::make_shared<GameObject>();
	scene.Add(pickle);
	pickle->SetPosition(0, 0);
	
	rotComp = pickle->AddComponent<RotatorComponent>(pickle);
	rotComp->SetRadius(40);
	rotComp->SetSpeed(-5);
	
	pickle->SetParent(hotDog);	// will change position to parent
	rotComp->SetCenterToObjectPos();
	
	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");
	
	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);

	// test for remove component
	//go = std::make_shared<GameObject>();
	//scene.Add(go);
	//
	//go->AddComponent<TextComponent>(go);
	//go->RemoveComponent<TextComponent>();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}