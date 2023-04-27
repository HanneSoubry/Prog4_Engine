#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::ScoreComponent::SetEvent(Event event)
{
	m_Event = event;
	m_EventSet = true;
}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;

	if (m_EventSet)
		Notify(*GetOwner().get(), m_Event);
}

void dae::ScoreComponent::IncreaseScore(int points)
{
	m_Score += points;

	if (m_EventSet)
		Notify(*GetOwner().get(), m_Event);
}

int* dae::ScoreComponent::GetScorePtr()
{
	return &m_Score;
}

int dae::ScoreComponent::GetScore()
{
	return m_Score;
}
