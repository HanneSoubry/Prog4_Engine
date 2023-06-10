#pragma once
#include "Command.h"
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class MoveCommand final : public Command<glm::vec2>
	{
	public:
		MoveCommand(GameObject* pGameObject, float speed);
		~MoveCommand() = default;

		virtual void Execute(const glm::vec2& movementDirection) override;

	private:
		GameObject* m_pGameObject{};
		float m_MovementSpeed{};
	};

}
