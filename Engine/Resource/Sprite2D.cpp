#include "pch.h"
#include "Sprite2D.h"
#include "../Render/D2DRender.h"

Resource::Sprite2D::Sprite2D(const std::wstring& _path, SpriteData _data)
{
    type = ResourceType::Sprite2D;
    m_key = _path;
    m_spriteData = _data;

    ID2D1Bitmap* tempTexture = nullptr;

    if (_path.empty()) // 파일경로 없을 시 예외
        assert(false && "FilePath_is_Empty");

    HRESULT hr;
    IWICImagingFactory* imgFactory = D2DRender::GetIMGFactory();
    IWICBitmapDecoder* decoder = nullptr;
    IWICFormatConverter* converter = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;

    hr = imgFactory->CreateDecoderFromFilename(
        _path.c_str(),                       // Image to be decoded
        nullptr,                             // Do not prefer a particular vendor
        GENERIC_READ,                        // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,      // Cache metadata when needed
        &decoder                             // Pointer to the decoder
    );
    if (FAILED(hr)) assert(false && "Fail - TextureLoad");

    hr = decoder->GetFrame(0, &pFrame);
    if (FAILED(hr)) assert(false);

    hr = imgFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) assert(false);

    hr = converter->Initialize(
        pFrame,                          // Input bitmap to convert
        GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
        WICBitmapDitherTypeNone,         // Specified dither pattern
        nullptr,                         // Specify a particular palette 
        0.f,                             // Alpha threshold
        WICBitmapPaletteTypeCustom       // Palette translation type
    );
    if (FAILED(hr)) assert(false);

    hr = D2DRender::GetRenderTarget()->CreateBitmapFromWicBitmap(converter, nullptr, &tempTexture);
    if (FAILED(hr)) assert(false);

    D2D1_SIZE_F textureSize = tempTexture->GetSize();

    // 스프라이트 데이터를 자르고 m_spriteSheet에 추가
    int rows = static_cast<int>(m_spriteData.cut_by_grid.y);
    int cols = static_cast<int>(m_spriteData.cut_by_grid.x);
    D2D1_RECT_F rect;

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            D2D1_RECT_F rect;
            rect.left = m_spriteData.offset.left + x * (textureSize.width / cols + m_spriteData.margin.x * cols);
            rect.top = m_spriteData.offset.top + y * (textureSize.height / rows + m_spriteData.margin.y * rows);
            rect.right = rect.left + (textureSize.width / cols);
            rect.bottom = rect.top + (textureSize.height / rows);

            ID2D1Bitmap* sprite = nullptr;
            hr = D2DRender::GetRenderTarget()->CreateBitmap(
                D2D1::SizeU(static_cast<UINT32>(rect.right - rect.left), static_cast<UINT32>(rect.bottom - rect.top)),
                nullptr, 0, D2D1::BitmapProperties(tempTexture->GetPixelFormat()), &sprite);

            if (FAILED(hr))
                assert(false);

            ID2D1BitmapRenderTarget* bitmapRenderTarget = nullptr;
            hr = D2DRender::GetRenderTarget()->CreateCompatibleRenderTarget(D2D1::SizeF(rect.right - rect.left, rect.bottom - rect.top), &bitmapRenderTarget);
            if (FAILED(hr))
                assert(false);

            bitmapRenderTarget->BeginDraw();
            bitmapRenderTarget->DrawBitmap(tempTexture, D2D1::RectF(0, 0, rect.right - rect.left, rect.bottom - rect.top), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rect);
            hr = bitmapRenderTarget->EndDraw();
            if (FAILED(hr))
                assert(false);

            hr = bitmapRenderTarget->GetBitmap(&sprite);
            if (FAILED(hr))
                assert(false);

            m_spriteSheet.push_back(sprite);

            bitmapRenderTarget->Release();
        }
    }
    // 파일을 사용할 때마다 다시 만든다.
    if (converter) converter->Release();
    if (decoder) decoder->Release();
    if (pFrame) pFrame->Release();
    if (tempTexture) tempTexture->Release();
}

Resource::Sprite2D::~Sprite2D()
{
    for (ID2D1Bitmap* sprite : m_spriteSheet)
    {
        if (sprite) sprite->Release();
    }
}