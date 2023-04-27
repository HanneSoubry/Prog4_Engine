#pragma once
#include "ObserverAndSubject.h"
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent : public Subject, public BaseComponent
	{
	public:
		HealthComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void SetDieEvent(Event event);
		void SetLives(int lives);

		int* GetLivesPtr();
		int GetLives();
		void Die();
	private:

		int m_Lives{};
		bool m_EventSet = false;
		// could be playerDied, enemyDied...
		Event m_DieEvent{};
	};
}