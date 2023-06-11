#pragma once
#include "Command.h"
#include <string>
#include "GameManagerComponent.h"

namespace dae
{
	class SwitchGameCommand final : public BaseCommand
	{
	public:
		SwitchGameCommand(GameManagerComponent* gameManager);
		~SwitchGameCommand() = default;

		virtual void Execute() override;

	private:
		GameManagerComponent* m_GameManager{};
	};

}
