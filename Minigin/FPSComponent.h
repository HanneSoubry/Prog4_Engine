#pragma once
class FPSComponent
{
};

#include "BaseComponent.h"
#include <string>

namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pParent);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update() override;

	private:
		float m_Time{ 0.f };
		int m_Frames{ 0 };
	};
}