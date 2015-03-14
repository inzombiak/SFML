#include "EntityRenderer.h"
#include "Algorithms.h"
#include "Entity.h"
#include "ComponentBase.h"
#include "Debug.h"

void EntityRenderer::DivideIntoLayers()
{
	vector <std::shared_ptr<RenderComponent>> m_layer0;
	int layer;
	
	for (unsigned int i = 0; i < m_renderComponents[0].size(); ++i)
	{
		layer = m_renderComponents[0][i]->GetDepth();
		if (layer == 0)
			m_layer0.push_back(m_renderComponents[0][i]);
		else
		{
			if (m_renderComponents.size()  < layer + 1)
				m_renderComponents.resize(layer + 1);
			m_renderComponents[layer].push_back(m_renderComponents[0][i]);
		}
			
	}
	m_renderComponents[0] = m_layer0;
}

void EntityRenderer::Update(float dt)
{
	ZSortEntities();
	for (unsigned int i = 0; i < m_renderComponents.size(); ++i)
	{
		for (unsigned int j = 0; j < m_renderComponents[i].size(); ++j)
		{
			m_renderComponents[i][j]->Update(dt);
		}
	}
}

void EntityRenderer::Draw()
{
	for (unsigned int i = 0; i < m_renderComponents.size(); ++i)
	{
		for (unsigned int j = 0; j < m_renderComponents[i].size(); j++)
		{	
			if (!m_renderComponents[i][j]->GetInUse())
				m_renderComponents[i].erase(m_renderComponents[i].begin() + j);
			else if (m_renderComponents[i][j]->GetVisible())
				m_renderWindow.draw(m_renderComponents[i][j]->GetSprite());
		}
	}
}

StrongComponentPtr EntityRenderer::CreateRenderComponent()
{
	std::shared_ptr<RenderComponent> newRenderComp(new RenderComponent());
	m_renderComponents[0].push_back(newRenderComp);
	return newRenderComp;
}

StrongComponentPtr EntityRenderer::CreateRenderComponentOnLayer(int layer)
{
	std::shared_ptr<RenderComponent> newRenderComp(new RenderComponent());
	m_renderComponents[layer].push_back(newRenderComp);
	return newRenderComp;
}

void EntityRenderer::ZSortEntities()
{
	m_framesSinceLastSort++;
	//Only sort layer 1, 2 is UI and 0 is background
	if (m_framesSinceLastSort == MAX_SORT_FRAME_INTERVAL)
	{
		m_renderComponents[1] = Algorithms<std::shared_ptr<RenderComponent>>::MergeSortVector(m_renderComponents[1], CompareBottom);
		m_framesSinceLastSort = 0;
	}
}

bool EntityRenderer::CompareBottom(std::shared_ptr<RenderComponent>& rc1, std::shared_ptr<RenderComponent>& rc2)
{
	ComponentID id = ComponentBase::GetIDFromName(RenderComponent::COMPONENT_NAME);
	int depth1 = rc1->GetDepth();
	int depth2 = rc2->GetDepth();
	if (depth1 == depth2)
	{
		bool result = (rc1->GetSprite().getPosition().y + rc1->GetSprite().getGlobalBounds().height) < (rc2->GetSprite().getPosition().y + rc2->GetSprite().getGlobalBounds().height);

		return result;
	}
	else
		return depth1 < depth2;
}

vector<vector<std::shared_ptr<RenderComponent>>> EntityRenderer::m_renderComponents;