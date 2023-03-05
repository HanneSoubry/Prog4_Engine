#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> pOwner)
{
	m_pOwner = pOwner;
}
