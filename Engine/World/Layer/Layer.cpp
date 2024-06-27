#include "pch.h"
#include "Layer.h"

Layer::Layer(LayerType _type)
	: m_layerType(_type)
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
	for (Object*& obj : m_objectList)
	{
		if (obj->GetState() == GameState::Active)
		{
			obj->FixedUpdate();
		}
	}
}

void Layer::EarlyUpdate()
{
	for (Object*& obj : m_objectList)
	{
		if (obj->GetState() == GameState::Active)
		{
			obj->EarlyUpdate();
		}
	}
}

void Layer::Update()
{
	for (Object*& obj : m_objectList)
	{
		if (obj->GetState() == GameState::Active)
		{
			obj->Update();
		}
	}
}

void Layer::LateUpdate()
{
	for (Object*& obj : m_objectList)
	{
		if (obj->GetState() == GameState::Active)
		{
			obj->LateUpdate();
		}
	}
}

void Layer::Render()
{
	for (Object*& obj : m_objectList)
	{
		if (obj->GetState() == GameState::Active)
		{
			obj->Render();
		}
	}
}

void Layer::StateUpdate()
{
	SearchDestroy(m_objectList);
}

void Layer::SearchDestroy(std::vector<Object*>& _objList)
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
			if (!(*iter)->GetChild().empty())
			{
				// ��ͷ� �ڽ��� �ڽ� ����
				SearchDestroy((*iter)->GetChild());
			}
			++iter;
		}
	}
}
