#include "pch.h"
#include "Camera2D.h"
#include "Transform2D.h"
#include "../World/Object/Object.h"
#include "../World/Manager/WorldManager.h"
#include "../Render/D2DRender.h"

Camera2D::Camera2D()
    : viewportPosition({ 0.f,0.f }),
    viewportSize({ 0.f,0.f }),
    m_BackGroundColor(D2D1::ColorF(D2D1::ColorF::CadetBlue)),
    m_bitmap(nullptr)
{
    m_type = ComponentType::Camera;
    // �⺻ ���� ȭ�� �ػ󵵿� �°�
    RECT rc;
    GetClientRect(D2DRender::GetHWND(), &rc);
    D2D_SIZE_F res = { rc.right - rc.left, rc.bottom - rc.top };
    viewportSize = res;
}

Camera2D::~Camera2D()
{
}

void Camera2D::Initialize()
{
    D2DRender::GetRenderTarget()->CreateCompatibleRenderTarget(&m_bitmapRenderTarget);
}

void Camera2D::LateUpdate()
{
}

void Camera2D::Render()
{
    // bitmapRenderTarget�� BeginDraw ȣ��� ���ÿ� clearColor�� ������� Clear()�� ȣ�����ش�.
    m_bitmapRenderTarget->BeginDraw();
    m_bitmapRenderTarget->Clear(m_BackGroundColor);

    // ���� ����Ÿ���� �޾ƿ´�.
    ID2D1HwndRenderTarget* mainRenderTarget = D2DRender::GetRenderTarget();

    // ActiveWorld���� m_cullingLayer�� false�� ���̾ ��ȸ�ؼ� �ش� ������Ʈ�� Draw�� ȣ�� (���⼭ Render�޼ҵ�� ���� Camera*�� �Ű������� �޴´�.)
    World* activeWorld = WorldManager::GetActiveWorld();

    for (int i = 0; i < (int)LayerTag::SIZE; i++)
    {
        if (!m_cullingLayer[i])
        {
            for (Object*& obj : activeWorld->GetLayerList()[i]->GetObjectList())
            {
                if (!m_cullingTag[(int)obj->GetTag()])
                {
                    if (obj->GetTag() != ObjectTag::Camera || obj == gameObject)
                        obj->Draw(this);
                }
            }
        }
    }
    // ������Ʈ�� Render���� ī�޶��� bitmapRenderTarget�� ��� ������ ��ġ�� �������� EndDraw�� ȣ���Ѵ�.
    m_bitmapRenderTarget->EndDraw();

    // bitmapRenderTarget�� GetBitmap�޼ҵ带 ȣ���� m_bitmap�� ��Ʈ�ʵ����͸� �����Ѵ�.
    if (m_bitmap != nullptr) m_bitmap->Release();
    m_bitmapRenderTarget->GetBitmap(&m_bitmap);

    // ���� ����Ÿ�ٿ� ī�޶� ����ִ� ������Ʈ�� transform ���� ������� Drawbitmap�� �Ѵ�.
    D2D_RECT_F viewportRect = D2D1::RectF(viewportPosition.x, viewportPosition.y,
        viewportPosition.x + viewportSize.width, viewportPosition.y + viewportSize.height);

    mainRenderTarget->DrawBitmap(m_bitmap, viewportRect);
}

D2D1_MATRIX_3X2_F Camera2D::CameraMatrix()
{
    D2D1_MATRIX_3X2_F cameraMatrix = gameObject->transform->GetWorldMatrix();
    D2D1InvertMatrix(&cameraMatrix);
    RECT rc;
    GetClientRect(D2DRender::GetHWND(), &rc);
    D2D_SIZE_F res = { rc.right - rc.left, rc.bottom - rc.top };

    cameraMatrix =
        Transform2D::TranslateMatrix((-res.width) / 2, (-res.height) / 2) *
        cameraMatrix *
        Transform2D::TranslateMatrix((res.width) / 2, (res.height) / 2);
    return cameraMatrix;
}
