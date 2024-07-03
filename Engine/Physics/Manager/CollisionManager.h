#pragma once
#include "../../World/Manager/WorldManager.h"

union CollisionID
{
	struct
	{
		UINT32 left;
		UINT32 right;
	};

	UINT64 id;
};

class CollisionManager
{
public:

	static void FixedUpdate();

	static void SetCollsionLayer(LayerTag _layer, bool _isCheck);
	static bool GetCollisionID(Collider* left, Collider* right);
	static void SetCollisionID(Collider* left, Collider* right, bool enable);

private:

	static bool m_collisionLayer[(int)LayerTag::SIZE];
	static std::unordered_map<UINT64, bool> m_collisionMap;

	static int collisionCount; // 총 충돌체크를 몇번 했는지 출력해보려고 만듬
	static int objectCount; // 검사하는 오브젝트 수 출력해보려고 만듬
	static std::vector<Layer*> tempLayer;

	static void MergeCollisionLayer();
	static void IterateCollisionLayer();
	static void CheckCollider(Actor* _left, Actor* _right);
	static bool CheckCollision(Collider* _left, Collider* _right);

	static bool BoxToBox(BoxCollider2D* _left, BoxCollider2D* _right);
};