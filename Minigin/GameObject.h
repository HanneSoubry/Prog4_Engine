#pragma once
#include <memory>
#include <vector>

#include "Transform.h"

#include "TextComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update();
		void Render() const;
		void RenderImGui();

		void SetPosition(float x, float y);
		Transform GetTransform();

		void SetParent(std::shared_ptr<GameObject> pParent, bool worldPositionStays = false);

		template <typename T> std::shared_ptr<T> AddComponent(std::shared_ptr<GameObject> thisGameObject);
		template <typename T> void RemoveComponent();
		template <typename T> std::shared_ptr<T> GetComponent();
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
		std::weak_ptr<GameObject> m_pParent{};

		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;

		void RemoveChild(std::shared_ptr<GameObject> pChild);
		void AddChild(std::shared_ptr<GameObject> pChild);

		void SetPositionDirty();
		bool IsOneOfChildren(std::shared_ptr<GameObject> pChild);
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent(std::shared_ptr<GameObject> thisGameObject)
	{
		// should have only one component from the same type
		bool componentTypeExists = false;
		for (std::shared_ptr<BaseComponent> comp : m_pComponents)
		{
			if (typeid(comp) == typeid(std::shared_ptr<T>))
			{
				componentTypeExists = true;
				break;
			}
		}
		
		if (!componentTypeExists)
		{
			m_pComponents.push_back(std::make_shared<T>(thisGameObject));
			return std::dynamic_pointer_cast<T>(m_pComponents.back());
		}
	
		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		const int amount{ static_cast<int>(m_pComponents.size()) };
		for (int i{ 0 }; i < amount; ++i)
		{
			std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(m_pComponents[i]);
			if (casted != nullptr)	// cast success
			{
				m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), m_pComponents[i]));
			}
		}
	}

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent()
	{
		for (int i{ 0 }; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(m_pComponents[i]);
			if (casted != nullptr)	// cast success
			{
				return casted;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline bool GameObject::HasComponent()
	{
		for (int i{ 0 }; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(m_pComponents[i]);
			if (casted != nullptr)	// cast success
			{
				return true;
			}
		}

		return false;
	}
}
