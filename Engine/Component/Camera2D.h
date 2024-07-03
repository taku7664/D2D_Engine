#pragma once
#include "Component.h"

class Transform2D;
class Object;

class Camera2D
	: public Component
{
public:

    Camera2D();
    ~Camera2D();

    virtual void Initialize()final;
    virtual void LateUpdate()final;
    virtual void Render()final;

    void         SetLayerCulling(LayerTag _type, bool _isculling) { m_cullingLayer[(int)_type] = _isculling; }
    void         SetObjectTagCulling(ObjectTag _tag, bool _isculling) { m_cullingTag[(int)_tag] = _isculling; }
    void         SetBackGroundColor(D2D1_COLOR_F _color) { m_BackGroundColor = _color; }

    ID2D1BitmapRenderTarget* GetBitmapRenderTarget() { return m_bitmapRenderTarget; }
    D2D1_MATRIX_3X2_F CameraMatrix();

    Vector2 viewportPosition;   // 화면에 배치할 카메라 위치
    D2D_SIZE_F viewportSize;          // 화면에 배치할 카메라 사이즈

private:

    D2D_RECT_F m_viewportRect; // 카메라 배치 위치

    bool m_cullingLayer[(int)LayerTag::SIZE]{ false, }; // true일 시 렌더링에서 제외한다.
    bool m_cullingTag[(int)ObjectTag::SIZE]{ false, };   // true일 시 렌더링에서 제외한다.

    D2D1_COLOR_F m_BackGroundColor;
    ID2D1BitmapRenderTarget* m_bitmapRenderTarget; // 카메라기준 렌더링용 도화지(?)
    ID2D1Bitmap* m_bitmap; // 도화지를 비트맵으로 바꿔줭

};

