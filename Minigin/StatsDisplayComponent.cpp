
#include "StatsDisplayComponent.h"
#include "TextComponent.h"

dae::StatsDisplayComponent::StatsDisplayComponent(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::StatsDisplayComponent::SetTextTarget(std::shared_ptr<TextComponent> textComp)
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

void dae::StatsDisplayComponent::Notify(const GameObject&, Event)
{
	if (m_ValueSet)
	{
		std::string text{ m_Label + ": " + std::to_string(*m_pValue) };
		m_pTextComponent->SetText(text);
	}
}
