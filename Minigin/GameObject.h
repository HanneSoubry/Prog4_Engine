#pragma once
#include <memory>
#include <vector>

#include "Transform.h"

#include "TextComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final
	{
	public:
		void Update();
		void Render() const;
		void RenderImGui();

		void SetPosition(float x, float y);
		Transform GetTransform();

		void ChangeParent(GameObject* pParent, bool worldPositionStays = false);
		void MakeRootParent(std::unique_ptr<GameObject> pChildGameObject, bool worldPositionStays = false);
			// get the child back
		std::unique_ptr<GameObject> RemoveFromParent(GameObject* pChild, bool worldPositionStays = false);
			// delete the child
		void RemoveGameObject();

		template <typename T> T* AddComponent(GameObject* thisGameObject);
		template <typename T> void RemoveComponent();
		template <typename T> T* GetComponent();
		template <typename T> bool HasComponent();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_PositionDirty{};

		GameObject* m_pParent{};

		std::vector<std::unique_ptr<BaseComponent>> m_pComponents;
		std::vector<std::unique_ptr<GameObject>> m_pChildren;

		std::unique_ptr<GameObject> RemoveChild(GameObject* pChild);
		void AddChild(std::unique_ptr<GameObject> pChild);

		void SetPositionDirty();
		bool IsOneOfChildren(GameObject* pChild);
	};

	template<typename T>
	inline T* GameObject::AddComponent(GameObject* thisGameObject)
	{
		// should have only one component from the same type
		bool componentTypeExists = false;
		const int amount{ static_cast<int>(m_pComponents.size()) };
		for (int i{ 0 }; i < amount; ++i)
		{
			if (typeid(m_pComponents[i]) == typeid(std::unique_ptr<T>))
			{
				componentTypeExists = true;
				break;
			}
		}
		
		if (!componentTypeExists)
		{
			m_pComponents.push_back(std::make_unique<T>(thisGameObject));
			return dynamic_cast<T*>(m_pComponents.back().get());
		}
	
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		const int amount{ static_cast<int>(m_pComponents.size()) };
		for (int i{ 0 }; i < amount; ++i)
		{
			T* casted = dynamic_cast<T*>(m_pComponents[i].get());
			if (casted != nullptr)	// cast success
			{
				m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pComponents[i]));
			}
		}
	}

	template<typename T>
	inline T* GameObject::GetComponent()
	{
		for (int i{ 0 }; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			T* casted = dynamic_cast<T*>(m_pComponents[i].get());
			if (casted != nullptr)	// cast success
			{
				return dynamic_cast<T*>(m_pComponents[i].get());
			}
		}

		return nullptr;
	}

	template<typename T>
	inline bool GameObject::HasComponent()
	{
		for (int i{ 0 }; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			T* casted = dynamic_cast<T*>(m_pComponents[i].get());
			if (casted != nullptr)	// cast success
			{
				return true;
			}
		}

		return false;
	}
}
