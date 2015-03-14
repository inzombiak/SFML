#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "tinyxml2.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "custom_defininitions.h"

using tinyxml2::XMLElement;
class EntityFactory
{
public:
	bool CreateEntity(XMLElement* currEntityNode, StrongEntityPtr entity);
	//Entity CreateEntityByCopy(XMLElement* currEntityNode);
	bool CreateTileFromTmx(sf::Vector2f position, sf::Texture& texture, sf::IntRect textureRect,int depth, StrongEntityPtr entity);//For use with Tiled map files to creates tiles
	//Entity CreateTileFromTmxByCopy(sf::Vector2f position, sf::Texture& texture, sf::IntRect textureRect);
	bool CreateCollisionEntity(sf::Vector2f position, sf::Vector2f dimensions,int depth, StrongEntityPtr entity); //For use with Tiles map files to create collision boxes
	//Entity CreateCollisionEntityByCopy(sf::Vector2f position, sf::Vector2f dimensions);
	static EntityFactory* GetInstance()
	{
		static EntityFactory instance;
		return &instance;
	}
private:
	EntityFactory();
	EntityFactory(const EntityFactory &) { }
	EntityFactory &operator=(const EntityFactory &) { return *this; }
	
	static EntityID GetNextEntityID()
	{
		m_lastEntityID++;
		return m_lastEntityID;
	}

	StrongComponentPtr CreateComponent(XMLElement* currComponentNode);

	static EntityID m_lastEntityID;
};

#endif