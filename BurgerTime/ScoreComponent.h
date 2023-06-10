#pragma once

#include "ObserverAndSubject.h"
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent : public Subject, public BaseComponent
	{
	public:
		ScoreComponent(GameObject* pOwner);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void SetScore(int score);

		void IncreaseScore(int points);

		int* GetScorePtr();
		int GetScore();
	private:

		int m_Score{ 0 };
	};
}