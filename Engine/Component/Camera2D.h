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

    Vector2 viewportPosition;   // ȭ�鿡 ��ġ�� ī�޶� ��ġ
    D2D_SIZE_F viewportSize;          // ȭ�鿡 ��ġ�� ī�޶� ������

private:

    D2D_RECT_F m_viewportRect; // ī�޶� ��ġ ��ġ

    bool m_cullingLayer[(int)LayerTag::SIZE]{ false, }; // true�� �� ���������� �����Ѵ�.
    bool m_cullingTag[(int)ObjectTag::SIZE]{ false, };   // true�� �� ���������� �����Ѵ�.

    D2D1_COLOR_F m_BackGroundColor;
    ID2D1BitmapRenderTarget* m_bitmapRenderTarget; // ī�޶���� �������� ��ȭ��(?)
    ID2D1Bitmap* m_bitmap; // ��ȭ���� ��Ʈ������ �ٲ�a

};

