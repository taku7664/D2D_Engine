#include "pch.h"
#include "World.h"

Layer* World::m_persistentLayers[(int)LayerType::SIZE] = { nullptr };

World::World()
    : m_WorldTag(WorldTag::Default)
{
    if (m_persistentLayers[0] == nullptr)
    {
        for (int i = 0; i < (int)LayerType::SIZE; i++)
        {
            m_persistentLayers[i] = new Layer((LayerType)i);
        }
    }

    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        m_layers[i] = new Layer((LayerType)i);
    }

    // 메인카메라 생성
    Actor* camera = CreateObject<Actor>("Main_Camera", LayerType::Defalut, ObjectTag::Camera);
    camera->AddComponent<Camera2D>();
}

World::~World()
{
    for (Layer* layer : m_layers)
    {
        delete layer;
    }
}

void World::Release()
{
    for (Layer* layer : m_persistentLayers)
    {
        delete layer;
    }
}

void World::FixedUpdate()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i]) 
            m_layers[i]->FixedUpdate();
        if (m_persistentLayers[i]) 
            m_persistentLayers[i]->FixedUpdate();
    }
}

void World::EarlyUpdate()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i])
            m_layers[i]->EarlyUpdate();
        if (m_persistentLayers[i])
            m_persistentLayers[i]->EarlyUpdate();
    }
}

void World::Update()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i])
            m_layers[i]->Update();
        if (m_persistentLayers[i])
            m_persistentLayers[i]->Update();
    }
}

void World::LateUpdate()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i])
            m_layers[i]->LateUpdate();
        if (m_persistentLayers[i])
            m_persistentLayers[i]->LateUpdate();
    }
}

void World::StateUpdate()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i])
            m_layers[i]->StateUpdate();
        if (m_persistentLayers[i])
            m_persistentLayers[i]->StateUpdate();
    }
}

void World::Render()
{
    for (int i = 0; i < (int)LayerType::SIZE; i++)
    {
        if (m_layers[i])
            m_layers[i]->Render();
        if (m_persistentLayers[i])
            m_persistentLayers[i]->Render();
    }
}