#include "pch.h"
#include "CollisionManager.h"

bool CollisionManager::m_collisionLayer[(int)LayerTag::SIZE] = {false, };
int CollisionManager::collisionCount = 0;
int CollisionManager::objectCount = 0;
std::vector<Layer*> CollisionManager::tempLayer;

// �߰��ؾ� �� �� : �ڽ� �浹�� ��� ������ ���ΰ�....����... ��¥ ������ ��
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
	// �ӽ� ���Ϳ� ���극�̾�� �۽ý��Ͻ����̾ ��ħ (��ȸ�ϱ� ���Ϸ��� �׳� �Ѱ�)
	for (int i = 0; i < (int)LayerTag::SIZE; i++)
	{
		// �浹üũ�� �� ���̾ ��ġ�� �ʤ���
		if (m_collisionLayer[(int)i])
		{
			tempLayer.push_back(WorldManager::GetActiveWorld()->GetLayerList()[i]);
			objectCount += tempLayer.back()->GetObjectList().size(); // ������Ʈ �� ����
			tempLayer.push_back(WorldManager::GetActiveWorld()->GetPersistentLayers()[i]);
			objectCount += tempLayer.back()->GetObjectList().size(); // 22
		}
	}
}

void CollisionManager::CheckInteraction(Actor* _left, Actor* _right)
{

	collisionCount++; // �׳� �浹üũ�� ����ϴ��� ����

	// Actor�� dynmic_cast�� �����ߴ��� Ȯ��
	if (_left && _right)
	{
		// ������Ʈ�� �ݶ��̴��� �޾ƿ´�.
		Collider* _leftCollider = _left->GetComponent<Collider>();
		Collider* _rightCollider = _right->GetComponent<Collider>();
		// �Ѵ� �ݶ��̴��� ���� �ÿ��� �˻縦 �Ѵ�.
		if (_leftCollider && _rightCollider)
		{
			// �ݶ��̴� Ÿ���� �޾ƿ´�.
			ComponentType _leftColliderType = _leftCollider->GetType();
			ComponentType _rightColliderType = _rightCollider->GetType();
			// �ݶ��̴��� ������ ���� �ٸ� �浹 �˰����� ȣ���Ѵ�.
			if (_leftColliderType == ComponentType::BoxCollider2D && _rightColliderType == ComponentType::BoxCollider2D)
			{
				AABB(dynamic_cast<BoxCollider2D*>(_leftCollider), dynamic_cast<BoxCollider2D*>(_rightCollider));
			}
		}
	}
}


bool CollisionManager::AABB(BoxCollider2D* left, BoxCollider2D* _right)
{
	// �Ʒ��� �浹�˻� ����
	return false;
}

void CollisionManager::IterateCollisionLayer()
{
	// left���̾� ��ȸ
	for (int leftIndex = 0; leftIndex < tempLayer.size(); ++leftIndex)
	{
		// ��ȸ�� ���ʷ��̾��� ������Ʈ ����Ʈ�� ������
		auto& leftList = tempLayer[leftIndex]->GetObjectList();
		// ���̾��� ������Ʈ�� ��ȸ�ϸ� �˻��Ѵ�. 
		// left������Ʈ�� right������Ʈ�� ���Ǻб⸦ �� ������ �˻縦 ����
		for (auto _left = leftList.begin(); _left != leftList.end(); ++_left)
		{
			// ������Ʈ�� ���� �� �ִ� Actor���� Ȯ��
			Actor* left = dynamic_cast<Actor*>(*(_left));
			if (left)
			{
				// right���̾� ��ȸ. �̶� �ߺ� üũ�� ���԰� ���ÿ� �˻�ð��� �ٿ����Ѵ�.
				// (�̹� left������ �˻��� ���̾�� �����ؾߴ�� rightIndex = leftIndex�� ����)
				for (int rightIndex = leftIndex; rightIndex < tempLayer.size(); ++rightIndex)
				{
					// ��ȸ�� �����ʷ��̾��� ������Ʈ ����Ʈ�� ������
					auto& rightList = tempLayer[rightIndex]->GetObjectList();
					// �ڱ��ڽ��� �˻��ϴ� ���� ���ؾ��Ѵ�. ���� right������Ʈ�� left�� ������ �;��Ѵ�. (���� �������� �ߺ��˻縦 ���ϱ� ����).
					// left���̾�� right���̾ ������ right�ݺ��ڴ� left�� ������带 ����Ű�� �Ѵ�.(std::next()�Լ� �����µ� gpt���� �� ��)
					// left���̾�� right���̾ ���� ������ right�ݺ��ڴ� ������Ʈ ����Ʈ�� ó���� ����Ű�� �ȴ�.
					auto _right = (leftIndex == rightIndex) ? std::next(_left) : rightList.begin();
					// ������ right�ݺ��ڸ� �������� ������Ʈ��ȸ�� �����Ѵ�.
					for (; _right != rightList.end(); ++_right)
					{
						// ������Ʈ�� ���� �� �ִ� Actor���� Ȯ��
						Actor* right = dynamic_cast<Actor*>((*_right));
						if (right)
						{
							// �浹üũ�� �غ���.
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
	// �ƴ� �̷��� �����غ��ϱ� �ȴ��ܽ� �ڽĵ� �ֻ��� ������Ʈ�� �˻��ؾߴ�ϱ�
	CheckInteraction(_left, _right);
	Debug.Log(std::to_string(collisionCount) + (collisionCount >= 10 ? "" : " ") + "st CollisionCheck    " + _left->GetName() + " : " + _right->GetName());

	// _left�� �ڽĵ�� _right�� �ڽĵ��� ���Ͽ� �浹 �˻縦 ����
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
