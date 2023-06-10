#pragma once

#include "Command.h"
#include <memory>

namespace dae
{
	class GameObject;
	class ScoreComponent;

	class IncreaseScoreCommand final : public Command
	{
	public:
		IncreaseScoreCommand(GameObject* pGameObject, int pointIncrease);
		~IncreaseScoreCommand() = default;

		IncreaseScoreCommand(const IncreaseScoreCommand& other) = delete;
		IncreaseScoreCommand(IncreaseScoreCommand&& other) = delete;
		IncreaseScoreCommand& operator=(const IncreaseScoreCommand& other) = delete;
		IncreaseScoreCommand& operator=(IncreaseScoreCommand&& other) = delete;

		virtual void Execute() override;

	private:
		ScoreComponent* pScoreComp;
		int m_pointIncrease = 0;
	};

}
