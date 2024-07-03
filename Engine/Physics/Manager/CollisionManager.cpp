#include "pch.h"
#include "CollisionManager.h"

bool CollisionManager::m_collisionLayer[(int)LayerTag::SIZE] = {};
std::unordered_map<UINT64, bool> CollisionManager::m_collisionMap = {};
int CollisionManager::collisionCount = 0;
int CollisionManager::objectCount = 0;
std::vector<Layer*> CollisionManager::tempLayer;

void CollisionManager::FixedUpdate()
{
	collisionCount = 0;
	objectCount = 0;
	tempLayer.clear();

	MergeCollisionLayer();
	
	IterateCollisionLayer();
	//Debug.Log("Total Object Count : " + std::to_string(objectCount));
	//Debug.Log("Total Collision Check : " + std::to_string(collisionCount));
}

void CollisionManager::SetCollsionLayer(LayerTag _layerTag, bool _isCheck)
{
	m_collisionLayer[(int)_layerTag] = _isCheck;
}

bool CollisionManager::GetCollisionID(Collider* left, Collider* right)
{
	// 두 충돌체의  ID 확인
	CollisionID collisionID;
	collisionID.left = left->GetID();
	collisionID.right = right->GetID();

	// 이전 충돌정보를 검색한다.
	auto iter = m_collisionMap.find(collisionID.id);

	// 충돌정보가 없다면 충돌정보를 만들어준다.
	if (iter == m_collisionMap.end())
	{
		m_collisionMap.insert(std::make_pair(collisionID.id, false));
		iter = m_collisionMap.find(collisionID.id);
	}
	return iter->second;
}

void CollisionManager::SetCollisionID(Collider* left, Collider* right, bool enable)
{
	// 두 충돌체의  ID 확인
	CollisionID collisionID;
	collisionID.left = left->GetID();
	collisionID.right = right->GetID();

	// 이전 충돌정보를 검색한다.
	auto iter = m_collisionMap.find(collisionID.id);

	iter->second = enable;
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
		}
	}
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
							CheckCollider(left, right);
							//Debug.Log(std::to_string(collisionCount) + (collisionCount >= 10 ? "" : " ") +
								//"st CollisionCheck    " + left->GetName() + " : " + right->GetName());
						}
					}
				}
			}
		}
	}

}

void CollisionManager::CheckCollider(Actor* _left, Actor* _right)
{

	collisionCount++; // 그냥 충돌체크를 몇번하는지 누적

	// 오브젝트의 콜라이더를 받아온다.
	Collider* _leftCollider = _left->GetComponent<Collider>();
	Collider* _rightCollider = _right->GetComponent<Collider>();

	// 둘다 콜라이더가 있을 시에만 검사를 한다.
	if (_leftCollider && _rightCollider)
	{
		// ID값을 통해 서로의 충돌상태를 확인
		bool check = GetCollisionID(_leftCollider, _rightCollider);

		if (CheckCollision(_leftCollider, _rightCollider))
		{
			// 충돌중이지 않았으면 Enter
			if (check == false)
			{
				_leftCollider->OnCollisionEnter(_right);
				_rightCollider->OnCollisionEnter(_left);
				SetCollisionID(_leftCollider, _rightCollider, true);
			}
			// 이미 충돌중이었으면 Stay
			else if (check == true)
			{
				_leftCollider->OnCollisionStay(_right);
				_rightCollider->OnCollisionStay(_left);
			}
		}
		else
		{
			// 충돌하지 않았는데 이전 틱에 충돌중이었으면 Exit
			if (check == true)
			{
				_leftCollider->OnCollisionExit(_right);
				_rightCollider->OnCollisionExit(_left);
				SetCollisionID(_leftCollider, _rightCollider, false);
			}
		}
	}
}

bool CollisionManager::CheckCollision(Collider* _left, Collider* _right)
{
	// 콜라이더 타입을 받아온다.
	ComponentType _leftType = _left->GetType();
	ComponentType _rightType = _right->GetType();

	// 콜라이더의 종류에 따라 다른 충돌 알고리즘을 호출한다.
	if (_leftType == ComponentType::BoxCollider2D && _rightType == ComponentType::BoxCollider2D)
		return (BoxToBox(dynamic_cast<BoxCollider2D*>(_left), dynamic_cast<BoxCollider2D*>(_right)));
}

bool CollisionManager::BoxToBox(BoxCollider2D* _left, BoxCollider2D* _right)
{
	// 아래는 충돌검사 로직
	Vector2 leftTr = _left->gameObject->transform->WorldPosition() + _left->offset;
	Vector2 rightTr = _right->gameObject->transform->WorldPosition() + _right->offset;

	D2D1_RECT_F leftRect = { leftTr.x, leftTr.y, leftTr.x + _left->size.width, leftTr.y + _left->size.height };
	D2D1_RECT_F rightRect = { rightTr.x, rightTr.y, rightTr.x + _right->size.width, rightTr.y + _right->size.height };

	// 충돌 여부를 검사
	bool isColliding = (leftRect.left < rightRect.right && leftRect.right > rightRect.left &&
		leftRect.top < rightRect.bottom && leftRect.bottom > rightRect.top);

	return isColliding;
}