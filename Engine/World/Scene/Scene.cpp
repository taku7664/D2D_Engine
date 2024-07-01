#include "pch.h"
#include "Scene.h"

Layer* Scene::m_dontDestroyLayerList[(int)LayerType::SIZE] = { nullptr };

Scene::Scene()
    : m_sceneTag(SceneTag::Default)
{
    if (m_dontDestroyLayerList[0] == nullptr)
    {
        for (int i = 0; i < (int)LayerType::SIZE; i++)
        {
            m_dontDestroyLayerList[i] = new Layer((LayerType)i);
        }
    }

    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        m_layerList[i] = new Layer((LayerType)i);
    }

    // 메인카메라 생성
    Object* camera = CreateObject(LayerType::Defalut, ObjectTag::Camera, "Main_Camera");
    camera->AddComponent<Camera2D>();
}

Scene::~Scene()
{
    for (Layer* layer : m_layerList)
    {
        delete layer;
    }
}

Object* Scene::CreateObject(LayerType _type, ObjectTag _tag, std::string _name)
{
	Object* clone = new Object(_name, _tag);
    clone->SetLayerOwner(m_layerList[(int)_type]);
	m_layerList[(int)_type]->GetObjectList().push_back(clone);
	return clone;
}

Object* Scene::FindObject(std::wstring _key, LayerType _layer)
{
    return nullptr;
}

Object* Scene::FindObject(std::wstring _key)
{
    return nullptr;
}

void Scene::DontDestroyOnLoad(Object* _obj)
{
    for (auto it = _obj->GetLayerOwner()->GetObjectList().begin(); it != _obj->GetLayerOwner()->GetObjectList().end(); ++it)
    {
        if ((*it)->GetName() == _obj->GetName())
        {
            m_dontDestroyLayerList[(int)_obj->GetLayerOwner()->GetLayerType()]->GetObjectList().push_back(_obj);
            _obj->GetLayerOwner()->GetObjectList().erase(it);
            _obj->SetLayerOwner(m_dontDestroyLayerList[(int)_obj->GetLayerOwner()->GetLayerType()]);
            break;
        }
    }
}

void Scene::FixedUpdate()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->FixedUpdate();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->FixedUpdate();
        }
    }
}

void Scene::EarlyUpdate()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->EarlyUpdate();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->EarlyUpdate();
        }
    }
}

void Scene::Update()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->Update();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->Update();
        }
    }
}

void Scene::LateUpdate()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->LateUpdate();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->LateUpdate();
        }
    }
}

void Scene::StateUpdate()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->StateUpdate();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->StateUpdate();
        }
    }
}

void Scene::Render()
{
    for (Layer*& layer : m_layerList)
    {
        if (layer)
        {
            layer->Render();
        }
    }
    for (Layer*& layer : m_dontDestroyLayerList)
    {
        if (layer)
        {
            layer->Render();
        }
    }
}