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

void dae::GameObject::RenderImGui()
{
	for (std::shared_ptr<BaseComponent> comp : m_pComponents)
	{
		comp->RenderImGui();
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
		if (m_pParent.lock() == nullptr)
		{
			m_WorldTransform = m_LocalTransform;
		}
		else	// has a parent
		{
			glm::vec3 worldParent =  m_pParent.lock()->GetTransform().GetPosition();
			glm::vec3 local = m_LocalTransform.GetPosition();
			m_WorldTransform.SetPosition(worldParent.x + local.x, worldParent.y + local.y, worldParent.z + local.z);
		}
	}

	return m_WorldTransform;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent, bool worldPositionStays)
{
	// check if valid parent (not itself or one of this its children)
	if (shared_from_this() == pParent)
		return;

	if (IsOneOfChildren(pParent))
		return;

	// leave previous parent
	if (m_pParent.lock() != nullptr)
		m_pParent.lock()->RemoveChild(shared_from_this());

	m_pParent = pParent;

	if (m_pParent.lock() != nullptr)
	{
		// to into child-vector of new parent
		m_pParent.lock()->AddChild(shared_from_this());

		// update transform
		if (worldPositionStays)
		{
			// change local position to keep the same world position
			glm::vec3 world = m_WorldTransform.GetPosition();
			glm::vec3 parent = m_pParent.lock()->GetTransform().GetPosition();
			m_LocalTransform.SetPosition(world.x - parent.x, world.y - parent.y, world.z - parent.z);
		}
		else
		{
			// local position stays -> need to recalculate worldPos
			SetPositionDirty();
		}
	}
	else
	{
		// new parent == nullptr (to remove a child without giving it a new parent)
		// update transform
		if (worldPositionStays)
		{
			// change local position to keep the same world position
			m_LocalTransform.SetPosition(m_WorldTransform.GetPosition().x, m_WorldTransform.GetPosition().y, m_WorldTransform.GetPosition().z);
		}
		else
		{
			// local position stays -> need to recalculate worldPos
			SetPositionDirty();
		}
	}
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	const int amount{ static_cast<int>(m_pChildren.size()) };
	for (int i{ 0 }; i < amount; ++i)
	{
		if (m_pChildren[i] == pChild)
		{
			m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), m_pChildren[i]));
		}
	}
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild)
{
	m_pChildren.push_back(pChild);
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;
	for (std::shared_ptr<GameObject> pChild : m_pChildren)
	{
		pChild->SetPositionDirty();
	}
}

bool dae::GameObject::IsOneOfChildren(std::shared_ptr<GameObject> pChild)
{
	if (std::find(m_pChildren.begin(), m_pChildren.end(), pChild) != m_pChildren.end())
	{
		// not the end of the list == this child found
		return true;
	}
	
	for (std::shared_ptr<GameObject> c : m_pChildren)
	{
		if (c->IsOneOfChildren(pChild))
		{
			// child of this objects' children
			return true;
		}
	}

	// none found
	return false;
}
