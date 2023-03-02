#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		glm::vec3& GetPosition() { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position;
	};
}
