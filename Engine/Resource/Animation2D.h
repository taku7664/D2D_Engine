#pragma once
#include "Sprite2D.h"

struct AnimationData
{
	D2D1_RECT_F		rect;			// �̹������� �ϳ��� ����� ��� ������ �ִ���
	D2D1_VECTOR_2F	center;			// �ϳ��� FRAME���� ������� 0,0 ����  ������ ��ǥ
	FLOAT			duration;		// �ϳ��� ����� �׸� �ð�

	AnimationData()
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = 0;
		rect.bottom = 0;
		duration = 0;
		center.x = 0;
		center.y = 0;
	}

	AnimationData(float _left, float _top, float _right, float _bottom, float _centerX, float _centerY, float _dur)
	{
		rect.left = _left;
		rect.top = _top;
		rect.right = _right;
		rect.bottom = _bottom;
		center.x = _centerX;
		center.y = _centerY;
		duration = _dur;
	}
	AnimationData(D2D1_RECT_F _rect, float _centerX, float _centerY, float _dur)
	{
		rect = _rect;
		center.x = _centerX;
		center.y = _centerY;
		duration = _dur;
	}
};

namespace Resource
{
	class Animation2D
		: public Resource2D
	{
	public:
		Animation2D(std::wstring _key, Resource::Sprite2D* _sprite, std::wstring _csvPath);
		virtual ~Animation2D();
		std::vector<AnimationData>& GetFrameData() { return m_frameData; }
	private:
		Sprite2D* m_sprite;
		std::vector<AnimationData> m_frameData;
	};
}