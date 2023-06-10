#pragma once

#include "Command.h"
#include <memory>

namespace dae
{
	class GameObject;
	class ScoreComponent;

	class IncreaseScoreInputCommand final : public BaseCommand
	{
	public:
		IncreaseScoreInputCommand(GameObject* pGameObject, int pointIncrease);
		~IncreaseScoreInputCommand() = default;

		virtual void Execute() override;

	private:
		GameObject* m_pGameObject;
		ScoreComponent* m_pScoreComp;
		int m_pointIncrease = 0;
	};

}
