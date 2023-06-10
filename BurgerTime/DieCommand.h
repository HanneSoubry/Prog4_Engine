#pragma once

#include "Command.h"
#include <memory>

namespace dae
{
	class GameObject;
	class HealthComponent;

	class DieCommand final : public Command
	{
	public:
		DieCommand(GameObject* pGameObject);
		~DieCommand() = default;

		DieCommand(const DieCommand& other) = delete;
		DieCommand(DieCommand&& other) = delete;
		DieCommand& operator=(const DieCommand& other) = delete;
		DieCommand& operator=(DieCommand&& other) = delete;

		virtual void Execute() override;

	private:
		HealthComponent* pHealthComp;
	};

}