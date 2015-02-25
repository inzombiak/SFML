#include "GameObjectManagerNew.h"
#include "InputComponent.h"
#include "tinyxml2.h"
#include "Entity.h"
#include "Algorithms.h"

void GameObjectManagerNew::Update(float time)
{
	//	m_player->Update(time);
	//Move(time);
	//m_Player->Move(0, 1, time);
	//m_Player->Move(1, 0, time);
	//m_Player->End();

}

void GameObjectManagerNew::Move(float time)
{
	////m_Player->Move(1, 1, time);

	//for (vector<VisibleGameObject*>::iterator it = m_staticGameObjects.begin(); it != m_staticGameObjects.end(); ++it)
	//{
	//	if ((*it)->GetSolid())
	//	{
	//		//if (CheckCollision(m_Player->GetGlobalCollisionRectangle(), (*it)->GetGlobalCollisionRectangle()))
	//		//{
	//		//	//m_Player->Stop();
	//		//	int r = ResolveCollision((*m_Player), *(*it));
	//		//	if (r == 0)
	//		//		m_Player->SetGrounded(true);
	//		//	else if (r == 1)
	//		//		m_Player->SetVelocityY(0);
	//		//}
	//	}
	//}

	////m_Player->Move(1, 0, time);

	//for (vector<VisibleGameObject*>::iterator it = m_staticGameObjects.begin(); it != m_staticGameObjects.end(); ++it)
	//{
	//	if ((*it)->GetSolid())
	//	{
	//		/*if (CheckCollision(m_Player->GetGlobalCollisionRectangle(), (*it)->GetGlobalCollisionRectangle()))
	//		{
	//		ResolveCollision((*m_Player), *(*it));
	//		m_Player->SetVelocityX(0);
	//		}*/
	//	}
	//}
}

//int GameObjectManagerNew::ResolveCollision(StrongEntityPtr& obj1, StrongEntityPtr& obj2)
//{
//	/*float obj1HalfHeight = obj1.GetCollisionRectangle().height / 2;
//	float obj2HalfHeight = obj2.GetCollisionRectangle().height / 2;
//
//	float obj1HalfWidth = obj1.GetCollisionRectangle().width / 2;
//	float obj2HalfWidth = obj2.GetCollisionRectangle().width / 2;
//
//	float obj1X = obj1.GetPosition().x + obj1.GetCollisionRectangle().left + obj1HalfWidth;
//	float obj1Y = obj1.GetPosition().y + obj1.GetCollisionRectangle().top + obj1HalfHeight;
//	float obj2X = obj2.GetPosition().x + obj2.GetCollisionRectangle().left + obj2HalfWidth;
//	float obj2Y = obj2.GetPosition().y + obj2.GetCollisionRectangle().top + obj2HalfHeight;
//
//	float xDistance = abs(obj1X - obj2X);
//	float yDistance = abs(obj1Y - obj2Y);
//
//	float xOverlap = obj1HalfWidth + obj2HalfWidth - xDistance;
//	float yOverlap = obj1HalfHeight + obj2HalfHeight - yDistance;
//
//	if (abs(yOverlap) < 0.001)
//		yOverlap = 0.001;
//
//	int result = -1;
//
//	if (abs(xOverlap) > abs(yOverlap))
//	{
//		xOverlap = 0;
//		if (obj1Y < obj2Y)
//		{
//			yOverlap *= -1;
//			result = 0;
//		}
//		else
//			result = 1;
//	}
//	else
//	{
//		result = 3;
//		yOverlap = 0;
//		if (obj1X < obj2X)
//		{
//			xOverlap *= -1;
//		}
//		else
//		{
//		}
//	}
//	obj1.SetPosition(obj1.GetPosition().x + xOverlap, obj1.GetPosition().y + yOverlap);
//	return result;*/
//}

void GameObjectManagerNew::Draw(sf::RenderWindow &rw)
{
	for (vector<StrongEntityPtr*>::iterator it = m_staticGameObjects.begin(); it != m_staticGameObjects.end(); ++it)
	{
		(*it)->Draw(rw);
	}
	shared_ptr<RenderComponent> rc = static_pointer_cast<RenderComponent>(StrongComponentPtr(m_player->GetComponent(ComponentBase::GetIDFromName(RenderComponent::COMPONENT_NAME))));
	if (!m_player->GetComponent(ComponentBase::GetIDFromName(RenderComponent::COMPONENT_NAME)).expired())
	{
		sf::Sprite s = rc->GetSprite();
		rw.draw(s);
	}
	m_renderer.Draw(rw);
}

//bool GameObjectManagerNew::CheckCollision(sf::Rect<float>& r1, sf::Rect<float>& r2)
//{
//	bool result = r1.intersects(r2);
//	return result;
//}

void GameObjectManagerNew::LoadEntities(string filename)
{

	string f = "data/Entities.xml";

	tinyxml2::XMLDocument file;
	file.LoadFile(f.c_str());

	tinyxml2::XMLNode* pRoot = file.FirstChild();
	tinyxml2::XMLElement* pEntities = pRoot->FirstChildElement("Entities");
	tinyxml2::XMLElement* pEntity = pEntities->FirstChildElement("Entity");
	tinyxml2::XMLElement* pComp;
	StrongEntityPtr newEntity;
	while (pEntity != nullptr)
	{
		newEntity = m_entityFactory.CreateEntity(pEntity);
		if (newEntity)
		{
			if (newEntity->GetType().compare("Player"))
			{
				m_player = newEntity;
			}
			m_entities.push_back(newEntity);
		}
		pEntity = pEntity->NextSiblingElement("Entity");
	}
}

void GameObjectManagerNew::SetForegroundTiles(vector<StrongEntityPtr>& objects)
{
	m_entities.insert(objects.begin(), objects.end(), m_entities.end());
}

void GameObjectManagerNew::SetBackgroundTiles(vector<StrongEntityPtr>& objects)
{
	m_backgroundTiles = objects;
}

void GameObjectManagerNew::SetCollisionBoxes(vector<StrongEntityPtr>& tiles)
{
	m_colllisionBoxes = tiles;
}

WeakEntityPtr GameObjectManagerNew::GetPlayer()
{
	return m_player;
}

void GameObjectManagerNew::ZSortEntities()
{
	m_framesSinceLastSort++;

	if (m_framesSinceLastSort == MAX_SORT_FRAME_INTERVAL)
	{
		m_entities = 

		m_framesSinceLastSort = 0;
	}
}

bool GameObjectManagerNew::CompareBottom(StrongEntityPtr& entity1, StrongEntityPtr& entity2)
{

}

//vector<StrongEntityPtr*> GameObjectManagerNew::GetPossibleCollisions(StrongEntityPtr& object)
//{
//	//vector<int> possibleCollTileIndicies = LevelLoader::PossibleTiles(object.GetPosition());
//	vector<StrongEntityPtr*> result;
//
//	/*while (!possibleCollTileIndicies.empty())
//	{
//	result.push_back(m_levelTiles[possibleCollTileIndicies.back()]);
//	possibleCollTileIndicies.pop_back();
//	}*/
//
//	return result;
//}