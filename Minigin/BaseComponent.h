#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(std::shared_ptr<GameObject> pParent);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(){}
		virtual void Render() const {}

	protected:
		std::weak_ptr<GameObject> m_pParent;
	};
}
