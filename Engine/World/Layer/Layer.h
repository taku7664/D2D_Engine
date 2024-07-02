#pragma once
#include "../Object/Object.h"
#include "../Object/Actor/Actor.h"
#include "../Object/Widget/Text/DynamicText.h"
#include "../Object/Widget/Text/InputText.h"

class Layer
{
public:

	Layer(LayerTag _type);
	~Layer();

	void FixedUpdate();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void StateUpdate();
	void ProcessDestroy(std::vector<Object*>& _objList);

	LayerTag GetLayerTag() { return m_layerTag; }
	std::vector<Object*>& GetObjectList() { return m_objectList; }

private:

	LayerTag m_layerTag;
	std::vector<Object*> m_objectList;
};

