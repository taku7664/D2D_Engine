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

			// duration���� ũ��
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
	Vector2 center = { (size.width / 2) + offset.x, (size.height / 2) + offset.y }; // offset�� ���� �߽����� �� �Ű��ٱ�? �� ���� �׽�Ʈ�� �ʿ��� <- �ߵȴ�!

	// �߾��� ������ ȸ�� �� ������ ��ȯ ��� ����
	D2D1_MATRIX_3X2_F transform =
		Transform2D::TranslateMatrix(-center.x, -center.y) * // �̹����� �߽��࿡ �������� ����ؼ� �̵�
		tr->GetWorldMatrix() *								 // ���� ��ȯ ����
		Transform2D::TranslateMatrix(center.x, center.y) *   // �ٽ� ���� ��ġ�� �̵�
		_camera->CameraMatrix();							 // ���������� ī�޶� ��ȯ ����

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
