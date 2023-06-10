#pragma once

#include "Command.h"
#include <memory>

namespace dae
{
	class GameObject;
	class HealthComponent;

	class DieCommand final : public BaseCommand
	{
	public:
		DieCommand(GameObject* pGameObject);
		~DieCommand() = default;

		virtual void Execute() override;

	private:
		GameObject* m_pGameObject;
		HealthComponent* m_pHealthComp;
	};

}