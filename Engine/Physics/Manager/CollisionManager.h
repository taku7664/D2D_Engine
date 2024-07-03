#pragma once
#include "../../World/Manager/WorldManager.h"

class CollisionManager
{
public:

	static void FixedUpdate();

	static void SetCollsionLayer(LayerTag _layer, bool _isCheck);
	

private:

	static bool m_collisionLayer[(int)LayerTag::SIZE];

	static int collisionCount; // �� �浹üũ�� ��� �ߴ��� ����غ����� ����
	static int objectCount; // �˻��ϴ� ������Ʈ �� ����غ����� ����
	static std::vector<Layer*> tempLayer;

	static void MergeCollisionLayer();
	static void IterateCollisionLayer();
	static void CheckCollision(Actor* _left, Actor* _right);

	static bool AABB(BoxCollider2D* _left, BoxCollider2D* _right);
};