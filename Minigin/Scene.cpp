#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name)
	, m_pRoot(std::make_unique<GameObject>()) 
{}

Scene::~Scene() = default;

GameObject* Scene::Add(std::unique_ptr<GameObject> object)
{
	auto child = object.get();
	m_pRoot->MakeRootParent(std::move(object), true);
	return child;
}

std::unique_ptr<GameObject> Scene::Remove(GameObject* object)
{
	// give back the object
	return m_pRoot->RemoveFromParent(object, true);
}

void Scene::DeleteAll()
{
	// make new empty root object
	// unique ptr will call destructor for previous root
	// all children are unique ptrs too (-> also destroyed)
	m_pRoot = std::make_unique<GameObject>();
}

void Scene::Update()
{
	m_pRoot->Update();
}

void Scene::Render() const
{
	m_pRoot->Render();
}

void dae::Scene::RenderImGui()
{
	m_pRoot->RenderImGui();
}

