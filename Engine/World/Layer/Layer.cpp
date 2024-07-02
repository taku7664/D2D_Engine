#include "pch.h"
#include "Layer.h"

Layer::Layer(LayerTag _type)
	: m_layerTag(_type)
{
}

Layer::~Layer()
{
	// ������Ʈ �Ҵ� ����
	for (Object*& obj : m_objectList) {
		delete obj;
	}
}


void Layer::FixedUpdate()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		if (m_objectList[i]->GetState() == GameState::Active)
		{
			m_objectList[i]->FixedUpdate();
		}
	}
}

void Layer::EarlyUpdate()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		if (m_objectList[i]->GetState() == GameState::Active)
		{
			m_objectList[i]->EarlyUpdate();
		}
	}
}

void Layer::Update()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		if (m_objectList[i]->GetState() == GameState::Active)
		{
			m_objectList[i]->Update();
		}
	}
}

void Layer::LateUpdate()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		if (m_objectList[i]->GetState() == GameState::Active)
		{
			m_objectList[i]->LateUpdate();
		}
	}
}

void Layer::Render()
{
	for (int i = 0; i < m_objectList.size(); i++)
	{
		if (m_objectList[i]->GetState() == GameState::Active)
		{
			m_objectList[i]->Render();
		}
	}
}

void Layer::StateUpdate()
{
	ProcessDestroy(m_objectList);
}

void Layer::ProcessDestroy(std::vector<Object*>& _objList)
{
	for (auto iter = _objList.begin(); iter != _objList.end(); )
	{
		if ((*iter)->GetState() == GameState::Destroy)
		{
			delete* iter;
			iter = _objList.erase(iter);
		}
		else
		{
			// ActorŬ������ �ڽİ˻絵 �غ����Ѵ�
			Actor* actor = dynamic_cast<Actor*>(*iter);
			if ((*iter)->GetType() == ObjectType::Actor)
			{

			}
			if (actor && !actor->GetChild().empty())
			{
				// ��ͷ� �ڽ��� �ڽ� ����
				ProcessDestroy(actor->GetChild());
			}
			++iter;
		}
	}
}
