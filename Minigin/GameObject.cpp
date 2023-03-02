#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


