#include "pch.h"
#include "CollisionManager.h"

bool CollisionManager::m_collisionLayer[(int)LayerTag::SIZE] = {false, };
int CollisionManager::collisionCount = 0;
int CollisionManager::objectCount = 0;
std::vector<Layer*> CollisionManager::tempLayer;

// 추가해야 될 것 : 자식 충돌은 어떻게 구현할 것인가....ㅁㅊ... 진짜 난제다 후
void CollisionManager::FixedUpdate()
{
	collisionCount = 0;
	objectCount = 0;
	tempLayer.clear();

	MergeCollisionLayer();
	
	IterateCollisionLayer();
	Debug.Log("Total Object Count : " + std::to_string(objectCount));
	Debug.Log("Total Collision Check : " + std::to_string(collisionCount));
}

void CollisionManager::SetCollsionLayer(LayerTag _layerTag, bool _isCheck)
{
	m_collisionLayer[(int)_layerTag] = _isCheck;
}


void CollisionManager::MergeCollisionLayer()
{
	// 임시 벡터에 서브레이어랑 퍼시스턴스레이어를 합침 (순회하기 편하려고 그냥 한거)
	for (int i = 0; i < (int)LayerTag::SIZE; i++)
	{
		// 충돌체크를 할 레이어만 합치면 됨ㅇㅇ
		if (m_collisionLayer[(int)i])
		{
			tempLayer.push_back(WorldManager::GetActiveWorld()->GetLayerList()[i]);
			objectCount += tempLayer.back()->GetObjectList().size(); // 오브젝트 수 누적
			tempLayer.push_back(WorldManager::GetActiveWorld()->GetPersistentLayers()[i]);
			objectCount += tempLayer.back()->GetObjectList().size(); // 22
		}
	}
}

void CollisionManager::CheckInteraction(Actor* _left, Actor* _right)
{

	collisionCount++; // 그냥 충돌체크를 몇번하는지 누적

	// Actor로 dynmic_cast에 성공했는지 확인
	if (_left && _right)
	{
		// 오브젝트의 콜라이더를 받아온다.
		Collider* _leftCollider = _left->GetComponent<Collider>();
		Collider* _rightCollider = _right->GetComponent<Collider>();
		// 둘다 콜라이더가 있을 시에만 검사를 한다.
		if (_leftCollider && _rightCollider)
		{
			// 콜라이더 타입을 받아온다.
			ComponentType _leftColliderType = _leftCollider->GetType();
			ComponentType _rightColliderType = _rightCollider->GetType();
			// 콜라이더의 종류에 따라 다른 충돌 알고리즘을 호출한다.
			if (_leftColliderType == ComponentType::BoxCollider2D && _rightColliderType == ComponentType::BoxCollider2D)
			{
				AABB(dynamic_cast<BoxCollider2D*>(_leftCollider), dynamic_cast<BoxCollider2D*>(_rightCollider));
			}
		}
	}
}


bool CollisionManager::AABB(BoxCollider2D* left, BoxCollider2D* _right)
{
	// 아래는 충돌검사 로직
	return false;
}

void CollisionManager::IterateCollisionLayer()
{
	// left레이어 순회
	for (int leftIndex = 0; leftIndex < tempLayer.size(); ++leftIndex)
	{
		// 순회할 왼쪽레이어의 오브젝트 리스트를 가져옴
		auto& leftList = tempLayer[leftIndex]->GetObjectList();
		// 레이어의 오브젝트를 순회하며 검사한다. 
		// left오브젝트와 right오브젝트의 조건분기를 잘 나눠서 검사를 시행
		for (auto _left = leftList.begin(); _left != leftList.end(); ++_left)
		{
			// 컴포넌트를 가질 수 있는 Actor인지 확인
			Actor* left = dynamic_cast<Actor*>(*(_left));
			if (left)
			{
				// right레이어 순회. 이때 중복 체크를 피함과 동시에 검사시간을 줄여야한다.
				// (이미 left측에서 검사한 레이어는 제외해야대니 rightIndex = leftIndex로 해줌)
				for (int rightIndex = leftIndex; rightIndex < tempLayer.size(); ++rightIndex)
				{
					// 순회할 오른쪽레이어의 오브젝트 리스트를 가져옴
					auto& rightList = tempLayer[rightIndex]->GetObjectList();
					// 자기자신을 검사하는 것은 피해야한다. 또한 right오브젝트는 left의 다음에 와야한다. (누차 말하지만 중복검사를 피하기 위함).
					// left레이어와 right레이어가 같으면 right반복자는 left의 다음노드를 가르키게 한다.(std::next()함수 몰랐는데 gpt덕에 앎 ㄳ)
					// left레이어와 right레이어가 같지 않으면 right반복자는 오브젝트 리스트의 처음을 가리키면 된다.
					auto _right = (leftIndex == rightIndex) ? std::next(_left) : rightList.begin();
					// 설정한 right반복자를 기준으로 오브젝트순회를 시작한다.
					for (; _right != rightList.end(); ++_right)
					{
						// 컴포넌트를 가질 수 있는 Actor인지 확인
						Actor* right = dynamic_cast<Actor*>((*_right));
						if (right)
						{
							// 충돌체크를 해본다.
							CheckCollisions(left, right);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::CheckCollisions(Actor* _left, Actor* _right)
{
	// 아니 이러면 생각해보니까 안대잔슴 자식도 최상위 오브젝트를 검사해야대니까
	CheckInteraction(_left, _right);
	Debug.Log(std::to_string(collisionCount) + (collisionCount >= 10 ? "" : " ") + "st CollisionCheck    " + _left->GetName() + " : " + _right->GetName());

	// _left의 자식들과 _right의 자식들을 비교하여 충돌 검사를 수행
	const std::vector<Object*> tempList = Utillity.MergeVectors(_left->GetChild(), _right->GetChild());

	if (!tempList.empty())
	{
		objectCount += tempList.size();
		for (int i = 0; i < tempList.size(); i++)
		{
			Actor* leftChild = dynamic_cast<Actor*>(tempList[i]);
			if (leftChild)
			{
				for (int j = i + 1; j < tempList.size(); j++)
				{
					Actor* rightChild = dynamic_cast<Actor*>(tempList[j]);
					if (rightChild)
					{
						CheckInteraction(leftChild, rightChild);
						Debug.Log(std::to_string(collisionCount) + (collisionCount >= 10 ? "" : " ") + "st CollisionCheck    " + leftChild->GetName() + " : " + rightChild->GetName());
					}
				}
			}
		}
	}
}
