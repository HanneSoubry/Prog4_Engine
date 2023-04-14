#pragma once

#include "ObserverAndSubject.h"
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent : public Subject, public BaseComponent
	{
	public:
		ScoreComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		// score changed event
		void SetEvent(Event event);
		void SetScore(int score);

		void IncreaseScore(int points);

		int* GetScorePtr();
		int GetScore();
	private:

		int m_Score{ 0 };
		bool m_EventSet = false;

		Event m_Event{};
	};
}