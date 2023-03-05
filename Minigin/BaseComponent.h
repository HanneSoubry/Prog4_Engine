#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(){}
		virtual void Render() const {}

	protected:
		std::shared_ptr<GameObject> GetOwner() const { return m_pOwner.lock(); } 

	private:
		std::weak_ptr<GameObject> m_pOwner;
	};
}
