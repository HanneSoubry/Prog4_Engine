#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(GameObject* pOwner)
{
	m_pOwner = pOwner;
}
