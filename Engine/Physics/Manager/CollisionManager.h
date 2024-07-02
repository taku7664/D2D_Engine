#pragma once
#include "../../World/Manager/WorldManager.h"

class CollisionManager
{
public:

	static void FixedUpdate();

	static void SetCollsionLayer(LayerTag _layer, bool _isCheck);
	// IntersectCheck
	static void CollisionCheck(Object* _left, Object* _right);
	static bool AABB(BoxCollider2D* left, BoxCollider2D* _right);

private:

	static bool m_collisionLayer[(int)LayerTag::SIZE];

};