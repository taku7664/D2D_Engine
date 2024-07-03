#pragma once
#include "Component.h"

class Object;
class WorldManager;

class Script : public Component
{
public:

	Script();
	~Script();

	virtual void Start() {} // ������Ʈ�� �߰��� ���� �ٷ� ȣ��˴ϴ�.

	virtual void Initialize() override
	{
		Start();
	}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void LateUpadte() {}

	// ��ũ��Ʈ���� ����ϴ� �Լ�
	void         Destroy(Object* _obj);
	void         SetPersistentObject(Object* _obj);
	template<typename T>
	T*			 FindObject(const std::wstring& _name, const LayerTag _tag = LayerTag::Defalut);

	// �ܺο��� ȣ��޴� �Լ� (�浹, ��ư, Ȱ��ȭ ���)
	virtual void OnEnable() {}; // ������Ʈ�� Ȱ��ȭ �Ǹ� ȣ��˴ϴ�.
	virtual void OnDisable() {}; // ������Ʈ�� ��Ȱ��ȭ �Ǹ� ȣ��˴ϴ�.
	virtual void OnDestroy() {}; // ������Ʈ�� �ı��� �� ȣ��˴ϴ�.
};

template<typename T>
T* Script::FindObject(const std::wstring& _name, const LayerTag _tag)
{
	WorldManager::GetActiveWorld()->FindObject<T>(_name, _tag);
}