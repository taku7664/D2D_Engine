#pragma once
#include "../Object/Object.h"
#include "../Object/Actor/Actor.h"
#include "../Object/Widget/Text/DynamicText.h"
#include "../Object/Widget/Text/InputText.h"

class Layer
{
public:

	Layer(LayerType _type);
	~Layer();

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void StateUpdate();
	void ProcessDestroy(std::vector<Object*>& _objList);

	LayerType GetLayerType() { return m_layerType; }
	std::vector<Object*>& GetObjectList() { return m_objectList; }

private:

	LayerType m_layerType;
	std::vector<Object*> m_objectList;
};

