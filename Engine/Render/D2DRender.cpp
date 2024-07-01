#include "pch.h"
#include "D2DRender.h"

HWND					D2DRender::m_hwnd = nullptr;
ID2D1Factory* D2DRender::m_factory = nullptr;
IWICImagingFactory* D2DRender::m_imgFactory = nullptr;
ID2D1HwndRenderTarget* D2DRender::m_renderTarget = nullptr;
ID2D1SolidColorBrush* D2DRender::m_brush = nullptr;

void D2DRender::Initialize(HWND _hwnd)
{
	m_hwnd = _hwnd;

	HRESULT check;

	check = CoInitialize(NULL);

	// 팩토리 초기화
	check = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	if (FAILED(check))
		assert(false);
	// Create WIC factory
	check = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_imgFactory)
	);
	// 렌더타겟 설정
	RECT rc;
	GetClientRect(m_hwnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	check = m_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(m_hwnd, size),
		&m_renderTarget);
	if (FAILED(check))
		assert(false);

	// 기본 브러쉬 생성
	check = m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_brush);
	if (FAILED(check))
		assert(false);
}

void D2DRender::BeginDraw()
{
	m_renderTarget->BeginDraw();

	m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
}

void D2DRender::EndDraw()
{
	m_renderTarget->EndDraw();
}

void D2DRender::Release()
{
	if (m_factory) m_factory->Release();
	if (m_imgFactory) m_imgFactory->Release();
	if (m_renderTarget) m_renderTarget->Release();
	if (m_brush) m_brush->Release();
	CoUninitialize();
}
