#pragma once

#include "BaseComponent.h"

namespace dae
{
	class HowToPlayUIComponent final : public BaseComponent
	{
	public:
		HowToPlayUIComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~HowToPlayUIComponent() override = default;
		HowToPlayUIComponent(const HowToPlayUIComponent& other) = delete;
		HowToPlayUIComponent(HowToPlayUIComponent&& other) = delete;
		HowToPlayUIComponent& operator=(const HowToPlayUIComponent& other) = delete;
		HowToPlayUIComponent& operator=(HowToPlayUIComponent&& other) = delete;

		void RenderImGui() override;
	};
}