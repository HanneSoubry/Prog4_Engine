#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Time.h"
#include <cmath>
#include <string>

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::FPSComponent::Update()
{
	m_Time += Time::GetInstance().ElapsedSeconds();
	float maxTime{ 1.f };
	++m_Frames;	// update called every frame

	if (m_Time >= maxTime)
	{
		if (m_pTextComponent == nullptr)
			return;	// safety check

		// calculate fps over last second
		float fps{ m_Frames / m_Time };
		int fpsRounded{ static_cast<int>(fps + 0.5f) };	// + 0.5f and round down -> correctly rounded value

		if (fpsRounded != m_LastFPS)
		{
			m_pTextComponent->SetText(std::to_string(fpsRounded) + " FPS");
			m_LastFPS = fpsRounded;
		}

		m_Time = 0;
		m_Frames = 0;
	}
}

void dae::FPSComponent::SetTextTarget(std::shared_ptr<TextComponent> textComp)
{
	m_pTextComponent = textComp;
}