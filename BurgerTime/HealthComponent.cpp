#include "HealthComponent.h"
#include "GameObject.h"

dae::HealthComponent::HealthComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::HealthComponent::SetDieEvent(Event event)
{
	m_DieEvent = event;
	m_EventSet = true;
}

void dae::HealthComponent::SetLives(int lives)
{
	m_Lives = lives;
}

int* dae::HealthComponent::GetLivesPtr()
{
	return &m_Lives;
}

int dae::HealthComponent::GetLives()
{
	return m_Lives;
}

void dae::HealthComponent::Die()
{
	--m_Lives;

	if (m_Lives < 0)
		m_Lives = 0;

	// if(m_Lives == 0)
	// game over?

	if(m_EventSet)
		Notify(*GetOwner().get(), m_DieEvent);
}
