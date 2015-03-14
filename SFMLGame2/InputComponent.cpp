#include "InputComponent.h"
#include "TransformComponent.h"
#include "InventoryComponent.h"
#include "SFML\Window.hpp"
#include "Entity.h"

bool InputComponent::Init(XMLElement* componentNode)
{
	return true;
}


void InputComponent::Update(float dt, sf::Event event)
{
	StrongComponentPtr compPtr = ConvertToStrongPtr<ComponentBase>(m_owner->GetComponent(GetIDFromName(TransformComponent::COMPONENT_NAME)));
	std::shared_ptr<TransformComponent> transComp = CastComponentToDerived<StrongComponentPtr,TransformComponent>(compPtr);
	float vx = 0, vy = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vx = 100.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vx = -100.0f;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		vy = -100.0f;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		vy = 100.0f;
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
	{
		StrongComponentPtr compPtr = ConvertToStrongPtr<ComponentBase>(m_owner->GetComponent(GetIDFromName(InventoryComponent::COMPONENT_NAME)));
		std::shared_ptr<InventoryComponent> invComp = CastComponentToDerived<StrongComponentPtr, InventoryComponent>(compPtr);
		invComp->ToggleDisplay();
	}

	transComp->SetSpeed(sf::Vector2f(vx, vy));

	return;
}

const char* InputComponent::COMPONENT_NAME = "InputComponent";