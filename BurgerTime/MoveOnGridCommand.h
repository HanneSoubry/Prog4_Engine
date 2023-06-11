#pragma once
#include "Command.h"
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class MoveOnGridCommand final : public Command<glm::vec2>
	{
	public:
		MoveOnGridCommand(GameObject* pGameObject, float speed, const glm::vec2& characterSize);
		~MoveOnGridCommand() = default;

		virtual void Execute(const glm::vec2& movementDirection) override;

	private:
		GameObject* m_pGameObject{};
		float m_MovementSpeed{};
		glm::vec2 m_Size{};
	};

}