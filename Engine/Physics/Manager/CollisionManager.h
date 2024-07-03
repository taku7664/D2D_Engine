#pragma once
#include "../../World/Manager/WorldManager.h"

class CollisionManager
{
public:

	static void FixedUpdate();

	static void SetCollsionLayer(LayerTag _layer, bool _isCheck);
	

private:

	static bool m_collisionLayer[(int)LayerTag::SIZE];

	static int collisionCount; // 총 충돌체크를 몇번 했는지 출력해보려고 만듬
	static int objectCount; // 검사하는 오브젝트 수 출력해보려고 만듬
	static std::vector<Layer*> tempLayer;

	static void MergeCollisionLayer();
	static void IterateCollisionLayer();
	static void CheckCollision(Actor* _left, Actor* _right);

	static bool AABB(BoxCollider2D* _left, BoxCollider2D* _right);
};