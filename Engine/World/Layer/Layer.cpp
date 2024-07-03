#include "pch.h"
#include "Layer.h"

Layer::Layer(LayerTag _type)
	: m_layerTag(_type)
{
}

Layer::~Layer()
{
	// 오브젝트 할당 해제
	for (Object* obj : m_objectList) {
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
	// depthLevel값에 따라 오름차 정렬
	SortingObject();
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
			++iter;
		}
	}
}

// 비교 함수 정의
bool CompareObject(const Object* obj1, const Object* obj2)
{
	return obj1->depthsLevel < obj2->depthsLevel;
}


void Layer::SortingObject()
{
	std::sort(m_objectList.begin(), m_objectList.end(), CompareObject);
}
