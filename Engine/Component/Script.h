#pragma once
#include "Component.h"

class Object;
class WorldManager;

class Script : public Component
{
public:

	Script();
	~Script();

	virtual void Start() {} // 컴포넌트를 추가한 직후 바로 호출됩니다.

	virtual void Initialize() override
	{
		Start();
	}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void LateUpadte() {}

	// 스크립트에서 사용하는 함수
	void         Destroy(Object* _obj);
	void         SetPersistentObject(Object* _obj);
	template<typename T>
	T*			 FindObject(const std::wstring& _name, const LayerTag _tag = LayerTag::Defalut);

	// 외부에서 호출받는 함수 (충돌, 버튼, 활성화 등등)
	virtual void OnEnable() {}; // 오브젝트가 활성화 되면 호출됩니다.
	virtual void OnDisable() {}; // 오브젝트가 비활성화 되면 호출됩니다.
	virtual void OnDestroy() {}; // 오브젝트가 파괴될 때 호출됩니다.
};

template<typename T>
T* Script::FindObject(const std::wstring& _name, const LayerTag _tag)
{
	WorldManager::GetActiveWorld()->FindObject<T>(_name, _tag);
}