#pragma once
#include "Std.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

class Writer : public Singleton<Writer>
{

private:
	friend class Singleton<Writer>;
public:
	ID2D1Factory* m_d2dFactory;
	IDWriteFactory* m_pDWriteFactory;
	ID2D1RenderTarget* m_d2dRT;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pTextColor;
	std::wstring			m_szDefaultText;
	IDWriteTextLayout* m_pTextLayout;
	ID2D1EllipseGeometry* m_pEllipseGeometry;

public:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();

public:
	bool		Set(IDXGISurface1* dxgiSurface);
	bool		Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0,0,0,1 });
	bool		Draw_circle(float x, float y, float rad , D2D1_COLOR_F color );

private:
	Writer();
public:
	~Writer();
};

