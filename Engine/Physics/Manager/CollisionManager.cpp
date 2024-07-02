#include "pch.h"
#include "CollisionManager.h"

bool CollisionManager::m_collisionLayer[(int)LayerTag::SIZE] = {false, };

void CollisionManager::FixedUpdate()
{
	int count = 0;
	int obj = 0;
	std::vector<Layer*> tempLayer;
	for (int i = 0; i < (int)LayerTag::SIZE; i++)
	{
		tempLayer.push_back(WorldManager::GetActiveWorld()->GetLayerList()[i]);
		tempLayer.push_back(WorldManager::GetActiveWorld()->GetPersistentLayers()[i]);
		obj += tempLayer[i]->GetObjectList().size();
		obj += tempLayer[i + 1]->GetObjectList().size();
	}
	Debug.Log("Total Object Count : " + std::to_string(obj));
	for (int leftIndex = 0; leftIndex < tempLayer.size(); ++leftIndex)
	{
		auto& leftList = tempLayer[leftIndex]->GetObjectList();
		for (auto left = leftList.begin(); left != leftList.end(); ++left)
		{
			for (int rightIndex = leftIndex; rightIndex < tempLayer.size(); ++rightIndex)
			{
				auto& rightList = tempLayer[rightIndex]->GetObjectList();
				auto right = (leftIndex == rightIndex) ? std::next(left) : rightList.begin();

				for (; right != rightList.end(); ++right)
				{
					count++;
					Debug.Log(std::to_string(count) + "st CollisionCheck : " + (*left)->GetName() + "_to_" + (*right)->GetName());
					CollisionCheck(*left, *right);
				}
			}
		}
	}
	Debug.Log("Total Collision Check : " + std::to_string(count));
}

void CollisionManager::SetCollsionLayer(LayerTag _layer, bool _isCheck)
{
	m_collisionLayer[(int)_layer] = _isCheck;
}

void CollisionManager::CollisionCheck(Object* _left, Object* _right)
{
	// 둘다 컴포넌트를 가질 수 있는 Actor여야 한다.
	Actor* left = dynamic_cast<Actor*>(_left);
	Actor* right = dynamic_cast<Actor*>(_right);
	// Actor로 dynmic_cast에 성공했는지 확인
	if (left && right)
	{
		// 오브젝트의 콜라이더를 받아온다.
		Collider* leftCollider = left->GetComponent<Collider>();
		Collider* rightCollider = right->GetComponent<Collider>();
		// 둘다 콜라이더가 있을 시에만 검사를 한다.
		if (leftCollider && rightCollider)
		{
			// 콜라이더 타입을 받아온다.
			ComponentType leftColliderType = leftCollider->GetType();
			ComponentType rightColliderType = rightCollider->GetType();
			// 콜라이더의 종류에 따라 다른 충돌 알고리즘을 호출한다.
			if (leftColliderType == ComponentType::BoxCollider2D && rightColliderType == ComponentType::BoxCollider2D)
			{
				AABB(dynamic_cast<BoxCollider2D*>(leftCollider), dynamic_cast<BoxCollider2D*>(rightCollider));
			}
		}
	}
}

bool CollisionManager::AABB(BoxCollider2D* left, BoxCollider2D* _right)
{
	// 아래는 충돌검사 로직
	return false;
}
