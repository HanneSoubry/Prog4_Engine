#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>

#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "MoveCommand.h"
#include "DieCommand.h"
#include "IncreaseScoreCommand.h"
#include "TestSoundCommand.h"
#include "LoadSceneCommand.h"

#include "TextComponent.h"
#include "RenderTextComponent.h"
#include "TextureComponent.h"
#include "RenderTextureComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "TrashTheCacheIntComponent.h"
#include "TrashTheCacheGO3DComponent.h"
#include "HealthComponent.h"
#include "StatsDisplayComponent.h"
#include "ScoreComponent.h"
#include "HowToPlayUIComponent.h"
#include "LevelLoaderComponent.h"
#include "RenderLevelTilesComponent.h"
#include "GameManagerComponent.h"

#include "ServiceLocator.h"
#include "SdlSoundSystem.h"

#include "Prefabs.h"

#include <memory>
#include <iostream>

using namespace dae;

void AddBackground(Scene& scene);
void AddFPSCounter(Scene& scene);
void AddRotatingSprites(Scene& scene);
void AddTrashTheCasheImGUI(Scene& scene);
void AddInputTest(Scene& scene);
void Add2MovableCharacters(Scene& scene);
void Add2PlayableCharacters(Scene& scene);
void TestSound();
void CreateLevel1(Scene& scene);

void load()
{
	// scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//AddBackground(scene);
	//AddFPSCounter(scene);
	//AddRotatingSprites(scene);
	//AddTrashTheCasheImGUI(scene);
	//AddInputTest(scene);					
	//Add2MovableCharacters(scene);			// movement input
	//Add2PlayableCharacters(scene);			// observer & event queue
	//TestSound();

	CreateLevel1(scene);
}

void CreateLevel1(Scene& scene)
{
	auto game = scene.Add(std::move(std::make_unique<GameObject>()));
	auto manager = game->AddComponent<GameManagerComponent>(game);
	manager->SetScene(&scene);
	manager->Initialize();
}

void AddBackground(Scene& scene)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Background
	auto go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(0, 0);

	auto textureComp = go->AddComponent<TextureComponent>(go);
	textureComp->SetTexture("background.tga");

	auto renderTextureComp = go->AddComponent<RenderTextureComponent>(go);
	renderTextureComp->SetTextureToRender(textureComp);

	// Title
	go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(80, 40);

	auto textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");

	auto renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);

	// Logo
	go = scene.Add(std::make_unique<GameObject>());
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
	auto go = scene.Add(std::make_unique<GameObject>());
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
	auto hotDog = scene.Add(std::make_unique<GameObject>());

	auto rotComp = hotDog->AddComponent<RotatorComponent>(hotDog);
	rotComp->SetCenter(320, 280);
	rotComp->SetRadius(40);
	rotComp->SetSpeed(3);

	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");

	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);

	// Mr Pickle
	auto pickle = scene.Add(std::make_unique<GameObject>());
	pickle->SetPosition(0, 0);

	rotComp = pickle->AddComponent<RotatorComponent>(pickle);
	rotComp->SetRadius(40);
	rotComp->SetSpeed(-5);

	pickle->ChangeParent(hotDog);	// will change position to parent
	rotComp->SetCenterToObjectPos();

	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");

	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);
}
void AddTrashTheCasheImGUI(Scene& scene)
{
	// ImGui trash the cache
	auto trashImGui = scene.Add(std::make_unique<GameObject>());
	
	trashImGui->AddComponent<TrashTheCacheIntComponent>(trashImGui);
	trashImGui->AddComponent<TrashTheCacheGO3DComponent>(trashImGui);
}
void AddInputTest(Scene& scene)
{
	auto inputTest = scene.Add(std::make_unique<GameObject>());
	inputTest->SetPosition(320, 280);
	
	auto textureComp = inputTest->AddComponent<TextureComponent>(inputTest);
	textureComp->SetTexture("MrPickle.png");
	
	auto renderTextureComp = inputTest->AddComponent<RenderTextureComponent>(inputTest);
	renderTextureComp->SetTextureToRender(textureComp);
	
	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDL_SCANCODE_LEFT),
									static_cast<unsigned int>(SDL_SCANCODE_RIGHT),
									static_cast<unsigned int>(SDL_SCANCODE_UP),
									static_cast<unsigned int>(SDL_SCANCODE_DOWN) };
	
	std::unique_ptr<Command<glm::vec2>> command{ std::move(std::make_unique<MoveCommand>(MoveCommand(inputTest, 100.f))) };
	InputManager::GetInstance().BindCommand(keys,
		InputManager::InputAction::Digital2DAxis,
		std::move(command));

	//InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::ControllerButton::LeftThumb),
	//										InputManager::InputAction::Analog2DAxis,
	//										std::make_unique<MoveCommand>(inputTest.get(), 100.f),
	//										0);
}
void Add2MovableCharacters(Scene& scene)
{
	// Mr Hot Dog
	auto hotDog = scene.Add(std::make_unique<GameObject>());
	hotDog->SetPosition(200, 300);
	
	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");
	
	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);
	
	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDL_SCANCODE_A),
									static_cast<unsigned int>(SDL_SCANCODE_D),
									static_cast<unsigned int>(SDL_SCANCODE_W),
									static_cast<unsigned int>(SDL_SCANCODE_S) };
	float speed{ 100.f };
	
	std::unique_ptr<Command<glm::vec2>> command{ std::move(std::make_unique<MoveCommand>(MoveCommand(hotDog, speed))) };
	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::move(command));
	
	// Mr Pickle
	auto pickle = scene.Add(std::make_unique<GameObject>());
	pickle->SetPosition(400, 300);
	
	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");
	
	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);
	
	keys = { static_cast<unsigned int>(XBoxController::DPadLeft),
			 static_cast<unsigned int>(XBoxController::DPadRight),
			 static_cast<unsigned int>(XBoxController::DPadUp),
			 static_cast<unsigned int>(XBoxController::DPadDown) };
	
	command = std::make_unique<MoveCommand>(MoveCommand(pickle, 2 * speed));
	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::move(command), 0);
}
void Add2PlayableCharacters(Scene& scene)
{
	// Mr Hot Dog
	auto hotDog = scene.Add(std::make_unique<GameObject>());
	hotDog->SetPosition(200, 300);
	
	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");
	
	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);
	
	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDL_SCANCODE_A),
									static_cast<unsigned int>(SDL_SCANCODE_D),
									static_cast<unsigned int>(SDL_SCANCODE_W),
									static_cast<unsigned int>(SDL_SCANCODE_S) };
	float speed{ 100.f };
	
	std::unique_ptr<Command<glm::vec2>> command{ std::move(std::make_unique<MoveCommand>(MoveCommand(hotDog, speed))) };
	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::move(command));
	
	// Lives
	auto healthComp = hotDog->AddComponent<HealthComponent>(hotDog);
	healthComp->SetLives(5);
	
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_E, InputManager::InputAction::Down, std::make_unique<DieCommand>(hotDog));
	
	// Points
	auto scoreComp = hotDog->AddComponent<ScoreComponent>(hotDog);
	scoreComp->SetScore(0);
	
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_Q, InputManager::InputAction::Down, std::make_unique<IncreaseScoreInputCommand>(hotDog, 100));
	
	// Stats display
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	
	// lives
	auto go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(10, 300);
	
	auto textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetColor({ 255, 255, 0 });
	textComp->SetText("Lives: --");
	
	auto renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);
	
	auto statsComp = go->AddComponent<StatsDisplayComponent>(go);
	statsComp->SetTextTarget(textComp);
	statsComp->SetLabel("Lives");
	statsComp->SetValuePtr(healthComp->GetLivesPtr());
	
	healthComp->AddObserver(statsComp);
	
	// points
	go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(10, 330);
	
	textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetColor({ 255, 255, 0 });
	textComp->SetText("Score: --");
	
	renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);
	
	statsComp = go->AddComponent<StatsDisplayComponent>(go);
	statsComp->SetTextTarget(textComp);
	statsComp->SetLabel("Score");
	statsComp->SetValuePtr(scoreComp->GetScorePtr());
	
	scoreComp->AddObserver(statsComp);
	
	// Mr Pickle
	auto pickle = scene.Add(std::make_unique<GameObject>());
	pickle->SetPosition(400, 300);
	
	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");
	
	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);
	
	command = std::move(std::make_unique<MoveCommand>(MoveCommand(pickle, speed)));
	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::LeftThumb), InputManager::InputAction::Analog2DAxis,
		std::move(command), 0);
	
	// Lives
	healthComp = pickle->AddComponent<HealthComponent>(pickle);
	healthComp->SetLives(5);
	
	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::LeftShoulder), 
		InputManager::InputAction::Down, std::make_unique<DieCommand>(pickle), 0);
	
	// Points
	scoreComp = pickle->AddComponent<ScoreComponent>(pickle);
	scoreComp->SetScore(0);
	
	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::RightShoulder), 
		InputManager::InputAction::Down, std::make_unique<IncreaseScoreInputCommand>(pickle, 100), 0);
	
	// Stats display
		// lives
	go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(10, 380);
	
	textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetColor({ 255, 0, 0 });
	textComp->SetText("Lives: --");
	
	renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);
	
	statsComp = go->AddComponent<StatsDisplayComponent>(go);
	statsComp->SetTextTarget(textComp);
	statsComp->SetLabel("Lives");
	statsComp->SetValuePtr(healthComp->GetLivesPtr());
	
	healthComp->AddObserver(statsComp);
	
	// points
	go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(10, 410);
	
	textComp = go->AddComponent<TextComponent>(go);
	textComp->SetFont(font);
	textComp->SetColor({ 255, 0, 0 });
	textComp->SetText("Score: --");
	
	renderTextComp = go->AddComponent<RenderTextComponent>(go);
	renderTextComp->SetTextToRender(textComp);
	
	statsComp = go->AddComponent<StatsDisplayComponent>(go);
	statsComp->SetTextTarget(textComp);
	statsComp->SetLabel("Score");
	statsComp->SetValuePtr(scoreComp->GetScorePtr());
	
	scoreComp->AddObserver(statsComp);
	
	// How to play
	go = scene.Add(std::make_unique<GameObject>());
	go->SetPosition(50, 50);
	
	go->AddComponent<HowToPlayUIComponent>(go);	
}
void TestSound()
{
	std::shared_ptr<SoundSystem> soundSystem;
	soundSystem.reset(new SdlSoundSystem());
	ServiceLocator::RegisterSoundSystem(soundSystem);

	auto ss = ServiceLocator::GetSoundSystem();
	ss->LoadSound("../Data/SfxJump.wav");
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_K, InputManager::InputAction::Down, std::make_unique<TestSoundCommand>("../Data/SfxJump.wav"));
}

// DON'T TOUCH	
int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}