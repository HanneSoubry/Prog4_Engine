#pragma once

#include "BaseComponent.h"
#include <string>
#include "ObserverAndSubject.h"

namespace dae
{
	class TextComponent;

	class StatsDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		StatsDisplayComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~StatsDisplayComponent() override = default;
		StatsDisplayComponent(const StatsDisplayComponent& other) = delete;
		StatsDisplayComponent(StatsDisplayComponent&& other) = delete;
		StatsDisplayComponent& operator=(const StatsDisplayComponent& other) = delete;
		StatsDisplayComponent& operator=(StatsDisplayComponent&& other) = delete;

		void SetTextTarget(std::shared_ptr<TextComponent> textComp);
		void SetValuePtr(int* value);
		void SetLabel(const std::string& label);

		virtual void Notify(const GameObject& actor, Event event) override;

	private:
		std::string m_Label{ "" };
		int* m_pValue{ nullptr };
		bool m_ValueSet{ false };

		std::shared_ptr<TextComponent> m_pTextComponent{ nullptr };
	};
}