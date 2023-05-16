#include "ScoreComponent.h"
#include "BurgerTimeEvents.h"

dae::ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;

	std::shared_ptr<Event> event{ new EventScoreChanged(score, true) };
	Notify(event);
}

void dae::ScoreComponent::IncreaseScore(int points)
{
	m_Score += points;

	std::shared_ptr<Event> event{ new EventScoreChanged(points) };
	Notify(event);
}

int* dae::ScoreComponent::GetScorePtr()
{
	return &m_Score;
}

int dae::ScoreComponent::GetScore()
{
	return m_Score;
}
