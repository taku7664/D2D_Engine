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
    // 기본 값은 화면 해상도에 맞게
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
    // bitmapRenderTarget의 BeginDraw 호출과 동시에 clearColor를 기반으로 Clear()를 호출해준다.
    m_bitmapRenderTarget->BeginDraw();
    m_bitmapRenderTarget->Clear(m_BackGroundColor);

    // 메인 렌더타겟을 받아온다.
    ID2D1HwndRenderTarget* mainRenderTarget = D2DRender::GetRenderTarget();

    // ActiveWorld에서 m_cullingLayer가 false인 레이어만 순회해서 해당 오브젝트의 Draw를 호출 (여기서 Render메소드는 현재 Camera*를 매개변수로 받는다.)
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
    // 오브젝트의 Render에서 카메라의 bitmapRenderTarget에 모든 렌더를 마치면 마지막에 EndDraw를 호출한다.
    m_bitmapRenderTarget->EndDraw();

    // bitmapRenderTarget의 GetBitmap메소드를 호출해 m_bitmap에 비트맵데이터를 저장한다.
    if (m_bitmap != nullptr) m_bitmap->Release();
    m_bitmapRenderTarget->GetBitmap(&m_bitmap);

    // 메인 렌더타겟에 카메라를 들고있는 오브젝트의 transform 값을 기반으로 Drawbitmap을 한다.
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
