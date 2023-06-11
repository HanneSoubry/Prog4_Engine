
#include "StatsDisplayComponent.h"
#include "TextComponent.h"
#include "BurgerTimeEvents.h"
#include <memory>

dae::StatsDisplayComponent::StatsDisplayComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::StatsDisplayComponent::SetTextTarget(TextComponent* textComp)
{
	m_pTextComponent = textComp;

	if (m_pValue != nullptr)
	{
		std::string text{ m_Label + ": " + std::to_string(*m_pValue) };
		m_pTextComponent->SetText(text);
	}
}

void dae::StatsDisplayComponent::SetValuePtr(int* value)
{
	m_pValue = value;
	m_ValueSet = true;

	if (m_pTextComponent != nullptr)
	{
		std::string text{ m_Label + ": " + std::to_string(*m_pValue) };
		m_pTextComponent->SetText(text);
	}
}

void dae::StatsDisplayComponent::SetLabel(const std::string& label)
{
	m_Label = label;

	if (m_pTextComponent != nullptr && m_pValue != nullptr)
	{
		std::string text{ m_Label + ": " + std::to_string(*m_pValue) };
		m_pTextComponent->SetText(text);
	}
}

void dae::StatsDisplayComponent::Notify(std::shared_ptr<Event> event)
{
	if (m_ValueSet)
	{
		std::string text{ m_Label + ": " + std::to_string(*m_pValue) };
		m_pTextComponent->SetText(text);

		// dynamic cast returns nullptr if pointer cast fails
		//auto castedEvent{ dynamic_cast<EventScoreChanged*>(event.get()) };
		//if(castedEvent != nullptr && *m_pValue >= 500)
		//{
		//	m_ReachedScore500 = true;
		//}
	}
}
