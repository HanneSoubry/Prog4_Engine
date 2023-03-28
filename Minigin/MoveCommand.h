#pragma once
#include "Command.h"
#include <memory>
namespace dae
{
	class GameObject;

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pGameObject, float speed);
		~MoveCommand() = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute() override;

	private:
		float m_MovementSpeed{};
	};

}
