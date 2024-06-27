#pragma once

class D2DRender
{
public:

	static void Initialize(HWND _hwnd);
	static void BeginDraw();
	static void EndDraw();
	static void UnInitialize();

	static HWND GetHWND() { return m_hwnd; }
	static ID2D1Factory* GetFactory() { return m_factory; }
	static IWICImagingFactory* GetIMGFactory() { return m_imgFactory; }
	static ID2D1HwndRenderTarget* GetRenderTarget() { return m_renderTarget; }
	static ID2D1SolidColorBrush* GetBrush() { return m_brush; }

private:

	static HWND m_hwnd;
	static ID2D1Factory* m_factory;
	static IWICImagingFactory* m_imgFactory;
	static ID2D1HwndRenderTarget* m_renderTarget;
	static ID2D1SolidColorBrush* m_brush;

};

