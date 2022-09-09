#include "Device.h"

struct SimpleVertex {
	float x;
	float y;
	float z;

	float r;
	float g;
	float b;
	float a;
};

class Sample : public Device
{
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;

public:
	HRESULT	CreateVertexBuffer();
	HRESULT	CreateVertexLayout();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	~Sample();
};