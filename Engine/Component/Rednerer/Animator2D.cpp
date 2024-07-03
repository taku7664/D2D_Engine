#include "pch.h"
#include "Animator2D.h"
#include "../../World/Object/Actor/Actor.h"
#include "../Camera2D.h"
#include "../Transform2D.h"
#include "../../Render/D2DRender.h"

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
	Transform2D* tr = gameObject->transform;

	if (m_activeAnimation == nullptr)
		return;

	size = m_activeAnimation->GetSprite(m_activeAnimation->GetFrameData()[currentFrame].index)->GetSize();
	Vector2 center = { (size.width / 2) + offset.x, (size.height / 2) + offset.y }; // offset이 과연 중심축을 잘 옮겨줄까? 에 대한 테스트가 필요함 <- 잘된다!

	// 중앙을 축으로 회전 및 뒤집기 변환 행렬 설정
	D2D1_MATRIX_3X2_F transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // 이미지의 중심축에 오프셋을 계산해서 이동
		tr->GetWorldMatrix() *								 // 월드 변환 적용
		Transform2D::TranslateMatrix(center.x, center.y) *   // 다시 원래 위치로 이동
		_camera->CameraMatrix();							 // 최종적으로 카메라 변환 적용

	renderTarget->SetTransform(transform);

	renderTarget->DrawBitmap(
		m_activeAnimation->GetSprite(m_activeAnimation->GetFrameData()[currentFrame].index),
		{ 0, 0, size.width, size.height },
		alpha);
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(center.x, center.y), 3.f, 3.f);
	renderTarget->DrawEllipse(ellipse, D2DRender::GetBrush(), 3.f);

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
