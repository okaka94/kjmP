#include "Writer.h"

bool		Writer::Set(IDXGISurface1* dxgiSurface) {
	
	D2D1_RENDER_TARGET_PROPERTIES	props;
	ZeroMemory(&props, sizeof(props));
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = 96;
	props.dpiY = 96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr = m_d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface, &props, &m_d2dRT);

	hr = m_d2dRT->CreateSolidColorBrush({ 0,0,0,1 }, &m_pTextColor);

	return true;
}

bool Writer::Init() {

	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2dFactory);
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriteFactory);
	hr = m_pDWriteFactory->CreateTextFormat(L"°íµñ", NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_ITALIC, DWRITE_FONT_STRETCH_NORMAL, 30, L"en-us", &m_pTextFormat);

	m_szDefaultText = L"OKAKA";
	hr = m_pDWriteFactory->CreateTextLayout(m_szDefaultText.c_str(), m_szDefaultText.size(), m_pTextFormat, g_rtClient.right, g_rtClient.bottom, &m_pTextLayout);

	return true;
}

bool Writer::Frame() {
	return true;
}

bool Writer::Render() {

	Draw(0, 0, m_szDefaultText, { 1,0,1,1 });
	return true;
}

bool Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color) {

	m_d2dRT->BeginDraw();

	D2D1_RECT_F rt = { x,y,g_rtClient.right,g_rtClient.bottom };
	m_pTextColor->SetColor(color);
	m_pTextColor->SetOpacity(1.0f);
	m_d2dRT->DrawText(text.c_str(), text.size(), m_pTextFormat, rt, m_pTextColor);
	m_d2dRT->EndDraw();

	return true;
}

bool Writer::Draw_circle(float x, float y, float rad , D2D1_COLOR_F color ) {

	m_d2dFactory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x, y), rad, rad),&m_pEllipseGeometry);
	m_d2dRT->BeginDraw();

	D2D1_RECT_F rt = { x,y,g_rtClient.right,g_rtClient.bottom };
	m_pTextColor->SetColor(color);
	m_pTextColor->SetOpacity(0.8f);
	m_d2dRT->DrawGeometry(m_pEllipseGeometry, m_pTextColor, 3);
	m_d2dRT->EndDraw();

	return true;
}

bool Writer::Release() {
	if (m_pTextLayout) m_pTextLayout->Release();
	if (m_pTextColor) m_pTextColor->Release();
	if (m_pEllipseGeometry) m_pEllipseGeometry->Release();
	if (m_pDWriteFactory) m_pDWriteFactory->Release();
	if (m_d2dRT) m_d2dRT->Release();
	if (m_d2dFactory) m_d2dFactory->Release();

	return true;
}