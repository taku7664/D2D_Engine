#include "pch.h"
#include "Animator2D.h"
#include "../../World/Object/Object.h"
#include "../Camera2D.h"
#include "../Transform2D.h"

Animator2D::Animator2D()
{
	m_type = ComponentType::Animator2D;
	m_activeAnimation = nullptr;
	currentFrame = 0;
	isLoop = true;
	isStop = false;
	m_frameCount = 0.f;
}

Animator2D::~Animator2D()
{
}

void Animator2D::Update()
{
	if (m_activeAnimation)
	{
		if (!isStop)
		{
			m_frameCount += Time::deltaTime;

			// duration보다 크면
			if (m_frameCount > m_activeAnimation->GetFrameData()[currentFrame].duration)
			{
				if (!End())
				{
					currentFrame++;
					m_frameCount = 0.f;
				}
				else if (End() && isLoop)
				{
					GotoAndPlay(0);
					m_frameCount = 0.f;
				}
			}
		}
	}
}

void Animator2D::Draw(Camera2D* _camera)
{
	ID2D1BitmapRenderTarget* renderTarget = _camera->GetBitmapRenderTarget();
	Transform2D* tr = m_owner->transform;

	if (m_activeAnimation == nullptr)
		return;

	D2D1_SIZE_F size = m_activeAnimation->GetSprite(m_activeAnimation->GetFrameData()[currentFrame].index)->GetSize();
	D2D1_VECTOR_2F center = { (size.width + offset.x) / 2 , (size.height + offset.y) / 2 }; // offset이 과연 중심축과 같이 움직이는게 맞을까?

	// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
	D2D1_MATRIX_3X2_F Transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // 이미지의 중심축에 오프셋을 계산해서 이동
		tr->GetWorldMatrix() * // 월드 변환 적용
		Transform2D::TranslateMatrix(center.x, center.y) * // 다시 원래 위치로 이동
		_camera->CameraMatrix(); // 최종적으로 카메라 변환 적용

	renderTarget->SetTransform(Transform);

	renderTarget->DrawBitmap(
		m_activeAnimation->GetSprite(m_activeAnimation->GetFrameData()[currentFrame].index),
		{ 0, 0, size.width, size.height },
		alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Animator2D::AddAnimation(std::string _key, Resource::Animation2D* _ani)
{
	if (_ani == nullptr)
		assert(false);

	if (FindAnimation(_key) != nullptr)
		return;

	m_animationList.insert(std::make_pair(_key, _ani));
}

Resource::Animation2D* Animator2D::FindAnimation(const std::string& _key)
{
	auto it = m_animationList.find(_key);
	if (it == m_animationList.end())
		return nullptr;
	return it->second;
}

void Animator2D::ActiveAnimation(const std::string& _key, bool _loop)
{
	Resource::Animation2D* _ani = FindAnimation(_key);
	if (_ani == nullptr)
		assert(false);
	if (_ani == m_activeAnimation)
		return;

	isLoop = _loop;
	currentFrame = 0;
	m_frameCount = 0.f;
	isStop = false;
	m_activeAnimation = _ani;
}

void Animator2D::GotoAndPlay(int _val)
{
	if (m_activeAnimation)
	{
		this->currentFrame = _val;
		this->isStop = false;
	}
}

void Animator2D::GotoAndStop(int _val)
{
	if (m_activeAnimation)
	{
		this->currentFrame = _val;
		this->isStop = true;
	}
}

void Animator2D::Play()
{
	if (m_activeAnimation)
		this->isStop = false;
}

void Animator2D::Stop()
{
	if (m_activeAnimation)
		this->isStop = true;
}

bool Animator2D::End()
{
	return (currentFrame >= m_activeAnimation->GetFrameData().size() - 1) && m_frameCount >= m_activeAnimation->GetFrameData()[currentFrame].duration;
}
