#include "HealthComponent.h"
#include "GameObject.h"
#include "BurgerTimeEvents.h"

dae::HealthComponent::HealthComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
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

	std::shared_ptr<Event> event{ new EventDamaged(1) };
	Notify(event);
}
