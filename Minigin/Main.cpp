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
#include "Scene.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "MoveCommand.h"

#include "TextComponent.h"
#include "RenderTextComponent.h"
#include "TextureComponent.h"
#include "RenderTextureComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TrashTheCacheIntComponent.h"
#include "TrashTheCacheGO3DComponent.h"

#include <memory>

using namespace dae;

void AddBackground(Scene& scene);
void AddFPSCounter(Scene& scene);
void AddRotatingSprites(Scene& scene);
void AddTrashTheCasheImGUI(Scene& scene);
void AddInputTest(Scene& scene);
void Add2MovableCharacters(Scene& scene);

void load()
{
	// scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");	

	AddBackground(scene);
	AddFPSCounter(scene);
	//AddRotatingSprites(scene);
	//AddTrashTheCasheImGUI(scene);
	AddInputTest(scene);
	Add2MovableCharacters(scene);

}

void AddBackground(Scene& scene)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

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
}

void AddFPSCounter(Scene& scene)
{
	auto fontFPS = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	// FPS Counter
	auto go = std::make_shared<GameObject>();
	scene.Add(go);

	go->SetPosition(2, 10);

	auto textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(fontFPS);
	textComp->SetColor({ 255, 255, 0 });
	textComp->SetText("-- FPS");

	auto renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);

	auto fpsComp = go->AddComponent<FPSComponent>(go);
	fpsComp->SetTextTarget(textComp);
}

void AddRotatingSprites(Scene& scene)
{
	// Mr Hot Dog
	auto hotDog = std::make_shared<GameObject>();
	scene.Add(hotDog);
	
	auto rotComp = hotDog->AddComponent<RotatorComponent>(hotDog);
	rotComp->SetCenter(320, 280);
	rotComp->SetRadius(40);
	rotComp->SetSpeed(3);
	
	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");
	
	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
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
}

void AddTrashTheCasheImGUI(Scene& scene)
{
	// ImGui trash the cache
	auto trashImGui = std::make_shared<GameObject>();
	scene.Add(trashImGui);

	auto trashIntComp = trashImGui->AddComponent<TrashTheCacheIntComponent>(trashImGui);
	auto trashGOComp = trashImGui->AddComponent<TrashTheCacheGO3DComponent>(trashImGui);
}

void AddInputTest(Scene& scene)
{
	auto inputTest = std::make_shared<GameObject>();
	scene.Add(inputTest);
	inputTest->SetPosition(320, 280);

	auto textureComp = inputTest->AddComponent<TextureComponent>(inputTest);
	textureComp->SetTexture("MrPickle.png");

	auto renderTextureComp = inputTest->AddComponent<RenderTextureComponent>(inputTest);
	renderTextureComp->SetTextureToRender(textureComp);

	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::ControllerButton::LeftThumb),
											InputManager::InputAction::Analog2DAxis,
											std::make_unique<MoveCommand>(inputTest.get(), 100.f),
											0);
}

void Add2MovableCharacters(Scene& /*scene*/)
{

}


// DON'T TOUCH	
int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}