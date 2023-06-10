#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(){}
		virtual void Render() const {}
		virtual void RenderImGui() {}

	protected:
		GameObject* GetOwner() const { return m_pOwner; } 

	private:
		GameObject* m_pOwner;
	};
}
