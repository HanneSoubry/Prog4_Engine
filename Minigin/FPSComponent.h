#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update() override;
		void SetTextTarget(std::shared_ptr<TextComponent> textComp);

	private:
		float m_Time{ 0.f };
		int m_Frames{ 0 };
		int m_LastFPS{};

		std::shared_ptr<TextComponent> m_pTextComponent{ nullptr };
	};
}