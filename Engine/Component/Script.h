#pragma once
#include "Component.h"

class Object;

class Script : public Component
{
public:

	Script();
	~Script();

	Object* gameobject; // ��ũ��Ʈ�� ���� ������Ʈ (=owner)

	virtual void Start() {} // ������Ʈ�� �߰��� ���� �ٷ� ȣ��˴ϴ�.

	virtual void Initialize() override {
		gameobject = GetOwner();
		Start();
	}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void LateUpadte() {}

	// ��ũ��Ʈ���� ����ϴ� �Լ�
	void         Destroy(Object* _obj);

	// �ܺο��� ȣ��޴� �Լ� (�浹, ��ư, Ȱ��ȭ ���)
	virtual void OnEnable() {}; // ������Ʈ�� Ȱ��ȭ �Ǹ� ȣ��˴ϴ�.
	virtual void OnDisable() {}; // ������Ʈ�� ��Ȱ��ȭ �Ǹ� ȣ��˴ϴ�.
	virtual void OnDestroy() {}; // ������Ʈ�� �ı��� �� ȣ��˴ϴ�.
};

