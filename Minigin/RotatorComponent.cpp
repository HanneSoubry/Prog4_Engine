#include "RotatorComponent.h"
#include "GameObject.h"
#include "Time.h"

dae::RotatorComponent::RotatorComponent(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::RotatorComponent::Update()
{
	m_Angle += m_Speed * Time::GetInstance().ElapsedSeconds();
	GetOwner()->SetPosition(m_Center.x + m_Radius * cosf(m_Angle), m_Center.y + m_Radius * sinf(m_Angle));
}

void dae::RotatorComponent::SetCenter(float centerX, float centerY)
{
	m_Center.x = centerX;
	m_Center.y = centerY;
}

void dae::RotatorComponent::SetRadius(float radius)
{
	// only positive radius accepted
	if(radius > 0)
		m_Radius = radius;
}

void dae::RotatorComponent::SetSpeed(float radiansPerSecond)
{
	m_Speed = radiansPerSecond;
}

void dae::RotatorComponent::SetCenterToObjectPos()
{
	glm::vec3 pos = GetOwner()->GetTransform().GetPosition();
	m_Center.x = pos.x;
	m_Center.y = pos.y;
}
