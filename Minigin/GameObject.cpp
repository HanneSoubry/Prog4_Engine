#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <iostream>

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	// update yourself
	for (int i{}; i < static_cast<int>(m_pComponents.size()); ++i)
	{
		m_pComponents[i]->Update();
	}

	// notify your children
	for (int i{}; i < static_cast<int>(m_pChildren.size()); ++i)
	{
		m_pChildren[i]->Update();
	}
}

void dae::GameObject::Render() const
{
	for (int i{}; i < static_cast<int>(m_pComponents.size()); ++i)
	{
		m_pComponents[i]->Render();
	}

	for (int i{}; i < static_cast<int>(m_pChildren.size()); ++i)
	{
		m_pChildren[i]->Render();
	}
}

void dae::GameObject::RenderImGui()
{
	for (int i{}; i < static_cast<int>(m_pComponents.size()); ++i)
	{
		m_pComponents[i]->RenderImGui();
	}

	for (int i{}; i < static_cast<int>(m_pChildren.size()); ++i)
	{
		m_pChildren[i]->RenderImGui();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 0.0f);
	SetPositionDirty();
}

dae::Transform dae::GameObject::GetTransform()
{
	if (m_PositionDirty)
	{
		// recalculate world position
		if (m_pParent == nullptr)
		{
			m_WorldTransform = m_LocalTransform;
		}
		else	// has a parent
		{
			glm::vec3 worldParent =  m_pParent->GetTransform().GetPosition();
			glm::vec3 local = m_LocalTransform.GetPosition();
			m_WorldTransform.SetPosition(worldParent.x + local.x, worldParent.y + local.y, worldParent.z + local.z);
		}
	}

	return m_WorldTransform;
}

void dae::GameObject::ChangeParent(GameObject* pParent, bool worldPositionStays)
{
	// check if valid parent (not itself or one of this its children)
	if (this == pParent)
	{
		std::cout << "Change parent was called, but pParent was himself\n";
		return;
	}

	if (IsOneOfChildren(pParent))
	{
		std::cout << "Change parent was called, but pParent was one of his children\n";
		return;
	}

	if (nullptr == pParent)
	{
		std::cout << "Change parent was called, but pParent was nullptr\n";
		return;
	}

	// leave previous parent
	std::unique_ptr<GameObject> myself;
	if (m_pParent != nullptr)
	{
		myself = m_pParent->RemoveChild(this);
	}
	else
	{
		std::cout << "Change parent was called, but this gameObject did not have a root parent yet\n";
		return;
	}

	m_pParent = pParent;

	// to into child-vector of new parent
	m_pParent->AddChild(std::move(myself));

	// update transform
	if (worldPositionStays)
	{
		// change local position to keep the same world position
		glm::vec3 world = GetTransform().GetPosition();
		glm::vec3 parent = m_pParent->GetTransform().GetPosition();
		m_LocalTransform.SetPosition(world.x - parent.x, world.y - parent.y, world.z - parent.z);
	}
	else
	{
		// local position stays -> need to recalculate worldPos
		SetPositionDirty();
	}
}

void dae::GameObject::MakeRootParent(std::unique_ptr<dae::GameObject> pChildGameObject, bool worldPositionStays)
{
	if (pChildGameObject->m_pParent != nullptr)
	{
		std::cout << "MakeRootParent called for child that already had a root. Call ChangeParent instead.\n";
		return;
	}

	// update transform
	if (worldPositionStays)
	{
		// change local position to keep the same world position
		glm::vec3 world = pChildGameObject->GetTransform().GetPosition();
		glm::vec3 parent = GetTransform().GetPosition();
		pChildGameObject->m_LocalTransform.SetPosition(world.x - parent.x, world.y - parent.y, world.z - parent.z);
	}
	else
	{
		// local position stays -> need to recalculate worldPos
		pChildGameObject->SetPositionDirty();
	}

	pChildGameObject->m_pParent = this;
	AddChild(std::move(pChildGameObject));
}

std::unique_ptr<dae::GameObject> dae::GameObject::RemoveFromParent(GameObject* pChild, bool worldPositionStays)
{
	auto child = RemoveChild(pChild);
	child->m_pParent = nullptr;

	// update transform
	if (worldPositionStays)
	{
		// change local position to keep the same world position
		glm::vec3 world = child->GetTransform().GetPosition();
		child->m_LocalTransform.SetPosition(world.x, world.y, world.z);
	}
	else
	{
		// local position stays -> need to recalculate worldPos
		child->SetPositionDirty();
	}

	return std::move(child);
}

void dae::GameObject::RemoveGameObject()
{
	if (m_pParent == nullptr)
	{
		std::cout << "RemoveGameObject called, but no parent to remove from\n";
		return;
	}

	// parent has unique_ptr to its child
	// if unique ptr is removed from the child list and goes out of scope
	// this gameobject will be deleted
	m_pParent->RemoveChild(this);
}

std::unique_ptr<dae::GameObject> dae::GameObject::RemoveChild(dae::GameObject* pChild)
{
	const int amount{ static_cast<int>( m_pChildren.size()) };
	for (int i{ 0 }; i < amount; ++i)
	{
		if (m_pChildren[i].get() == pChild)
		{
			// take child
			auto child = std::move(m_pChildren[i]);
			// replace last one on child's position
			m_pChildren[i] = std::move(m_pChildren.back());
			// remove last
			m_pChildren.resize(m_pChildren.size() - 1);

			return std::move(child);
		}
	}

	// not found
	std::cout << "Remove child called, but child not found\n";
	return nullptr;
}

void dae::GameObject::AddChild(std::unique_ptr<GameObject> pChild)
{
	m_pChildren.push_back(std::move(pChild));
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;
	for (int i{}; i < static_cast<int>(m_pChildren.size()); ++i)
	{
		m_pChildren[i]->SetPositionDirty();
	}
}

bool dae::GameObject::IsOneOfChildren(GameObject* pChild)
{
	const int amount{ static_cast<int>(m_pChildren.size()) };
	for (int i{ 0 }; i < amount; ++i)
	{
		if (m_pChildren[i].get() == pChild)
		{
			// child found
			return true;
		}
		else
		{
			if (m_pChildren[i]->IsOneOfChildren(pChild))
			{
				// child of this objects' children
				return true;
			}
		}
	}

	// none found
	return false;
}