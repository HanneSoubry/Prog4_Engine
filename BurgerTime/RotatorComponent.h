#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class RotatorComponent final : public BaseComponent
	{
	public:
		RotatorComponent(GameObject* pOwner);
		virtual ~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update() override;
		void SetCenter(float centerX, float centerY);
		void SetRadius(float radius);
		void SetSpeed(float radiansPerSecond);
		void SetCenterToObjectPos();

	private:
		glm::vec2 m_Center{};
		float m_Radius{10};
		float m_Speed{1};

		float m_Angle{};
	};
}
