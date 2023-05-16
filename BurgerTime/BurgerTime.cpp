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

#include "ServiceLocator.h"
#include "SdlSoundSystem.h"

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

void load()
{
	// scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	AddBackground(scene);
	AddFPSCounter(scene);
	//AddRotatingSprites(scene);
	//AddTrashTheCasheImGUI(scene);
	//AddInputTest(scene);					
	//Add2MovableCharacters(scene);			// movement input
	Add2PlayableCharacters(scene);			// observer & event queue

	// Gives link errors ???
	//std::shared_ptr<SoundSystem> soundSystem;
	//soundSystem.reset(new SdlSoundSystem());
	//ServiceLocator::RegisterSoundSystem(soundSystem);
	//
	//auto ss = ServiceLocator::GetSoundSystem();
	//ss->LoadSound("Data/SfxJump.wav");
	//ss->Play("Data/SfxJump.wav", 10);
	//InputManager::GetInstance().BindCommand(SDLK_k, InputManager::InputAction::Down, std::make_unique<TestSoundCommand>(nullptr));
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

	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDLK_LEFT),
									static_cast<unsigned int>(SDLK_RIGHT),
									static_cast<unsigned int>(SDLK_UP),
									static_cast<unsigned int>(SDLK_DOWN) };

	InputManager::GetInstance().BindCommand(keys,
		InputManager::InputAction::Digital2DAxis,
		std::make_unique<MoveCommand>(inputTest.get(), 100.f));

	//InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::ControllerButton::LeftThumb),
	//										InputManager::InputAction::Analog2DAxis,
	//										std::make_unique<MoveCommand>(inputTest.get(), 100.f),
	//										0);
}

void Add2MovableCharacters(Scene& scene)
{
	// Mr Hot Dog
	auto hotDog = std::make_shared<GameObject>();
	scene.Add(hotDog);
	hotDog->SetPosition(200, 300);

	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");

	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);

	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDLK_a),
									static_cast<unsigned int>(SDLK_d),
									static_cast<unsigned int>(SDLK_w),
									static_cast<unsigned int>(SDLK_s) };
	float speed{ 100.f };

	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::make_unique<MoveCommand>(hotDog.get(), speed));

	// Mr Pickle
	auto pickle = std::make_shared<GameObject>();
	scene.Add(pickle);
	pickle->SetPosition(400, 300);

	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");

	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);

	keys = { static_cast<unsigned int>(XBoxController::DPadLeft),
			 static_cast<unsigned int>(XBoxController::DPadRight),
			 static_cast<unsigned int>(XBoxController::DPadUp),
			 static_cast<unsigned int>(XBoxController::DPadDown) };

	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::make_unique<MoveCommand>(pickle.get(), 2 * speed), 0);
}

void Add2PlayableCharacters(Scene& scene)
{
	// Mr Hot Dog
	auto hotDog = std::make_shared<GameObject>();
	scene.Add(hotDog);
	hotDog->SetPosition(200, 300);

	auto textureComp = hotDog->AddComponent<TextureComponent>(hotDog);
	textureComp->SetTexture("MrHotDog.png");

	auto renderTextureComp = hotDog->AddComponent<RenderTextureComponent>(hotDog);
	renderTextureComp->SetTextureToRender(textureComp);

	std::vector<unsigned int> keys{ static_cast<unsigned int>(SDLK_a),
									static_cast<unsigned int>(SDLK_d),
									static_cast<unsigned int>(SDLK_w),
									static_cast<unsigned int>(SDLK_s) };
	float speed{ 100.f };

	InputManager::GetInstance().BindCommand(keys, InputManager::InputAction::Digital2DAxis,
		std::make_unique<MoveCommand>(hotDog.get(), speed));

	// Lives
	auto healthComp = hotDog->AddComponent<HealthComponent>(hotDog);
	healthComp->SetLives(5);

	InputManager::GetInstance().BindCommand(SDLK_e, InputManager::InputAction::Down, std::make_unique<DieCommand>(hotDog.get()));

	// Points
	auto scoreComp = hotDog->AddComponent<ScoreComponent>(hotDog);
	scoreComp->SetScore(0);

	InputManager::GetInstance().BindCommand(SDLK_q, InputManager::InputAction::Down, std::make_unique<IncreaseScoreCommand>(hotDog.get(), 100));

	// Stats display
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	// lives
	auto go = std::make_shared<GameObject>();
	scene.Add(go);
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

	healthComp->AddObserver(statsComp.get());

	// points
	go = std::make_shared<GameObject>();
	scene.Add(go);
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

	scoreComp->AddObserver(statsComp.get());

	// Mr Pickle
	auto pickle = std::make_shared<GameObject>();
	scene.Add(pickle);
	pickle->SetPosition(400, 300);

	textureComp = pickle->AddComponent<TextureComponent>(pickle);
	textureComp->SetTexture("MrPickle.png");

	renderTextureComp = pickle->AddComponent<RenderTextureComponent>(pickle);
	renderTextureComp->SetTextureToRender(textureComp);

	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::LeftThumb), InputManager::InputAction::Analog2DAxis,
		std::make_unique<MoveCommand>(pickle.get(), speed), 0);

	// Lives
	healthComp = pickle->AddComponent<HealthComponent>(pickle);
	healthComp->SetLives(5);

	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::LeftShoulder), InputManager::InputAction::Down, std::make_unique<DieCommand>(pickle.get()), 0);

	// Points
	scoreComp = pickle->AddComponent<ScoreComponent>(pickle);
	scoreComp->SetScore(0);

	InputManager::GetInstance().BindCommand(static_cast<unsigned int>(XBoxController::RightShoulder), InputManager::InputAction::Down, std::make_unique<IncreaseScoreCommand>(pickle.get(), 100), 0);

	// Stats display
		// lives
	go = std::make_shared<GameObject>();
	scene.Add(go);
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

	healthComp->AddObserver(statsComp.get());

	// points
	go = std::make_shared<GameObject>();
	scene.Add(go);
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

	scoreComp->AddObserver(statsComp.get());

	// How to play
	go = std::make_shared<GameObject>();
	scene.Add(go);
	go->SetPosition(50, 50);

	auto UIComp = go->AddComponent<HowToPlayUIComponent>(go);

}

// DON'T TOUCH	
int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}