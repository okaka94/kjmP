#include "Base_object.h"

void Base_object::Frame(float delta_time) {}

bool Base_object::Init() { return true; }
bool Base_object::Frame() { return true; }

HRESULT	Base_object::LoadTexture(std::wstring filename) {
	HRESULT hr;
	hr = DirectX::CreateWICTextureFromFile(m_pd3dDevice, m_pImmediateContext, filename.c_str(), &m_Texture, &m_pTextureSRV);

	return hr;
}

bool Base_object::Create(ID3D11Device* pd3dDevice , ID3D11DeviceContext* pImmediateContext , const wchar_t* texName, const wchar_t* shaderName) {
	SetDevice(pd3dDevice, pImmediateContext);

	if (FAILED(CreateVertexBuffer()))
		return false;

	if (FAILED(CreateShader(shaderName)))
		return false;

	if (FAILED(CreateVertexLayout()))
		return false;

	if (FAILED(LoadTexture(texName)))
		return false;

}


Base_object::~Base_object() {

}



void Base_object::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) {
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediateContext;

}

HRESULT Base_object::CreateVertexBuffer() {
	HRESULT hr;

	m_VertexList.resize(6);
	m_VertexList[0].p = { -0.5f,  0.5f, 0.0f };
	m_VertexList[0].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[0].t = { 0.0f,0.0f };

	m_VertexList[1].p = { 0.5f,  0.5f, 0.0f };
	m_VertexList[1].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[1].t = { 1.0f,0.0f };

	m_VertexList[2].p = { -0.5f, -0.5f, 0.0f };
	m_VertexList[2].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[2].t = { 0.0f,1.0f };

	m_VertexList[3].p = { -0.5f, -0.5f, 0.0f };
	m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[3].t = { 0.0f,1.0f };

	m_VertexList[4].p = { 0.5f,  0.5f, 0.0f };
	m_VertexList[4].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[4].t = { 1.0f,0.0f };

	m_VertexList[5].p = { 0.5f, -0.5f, 0.0f };
	m_VertexList[5].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[5].t = { 1.0f,1.0f };

	int num_vertex = m_VertexList.size();
	D3D11_BUFFER_DESC	bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(SimpleVertex) * num_vertex;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VertexList.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	return hr;
}

HRESULT	Base_object::CreateShader(std::wstring filename) {
	HRESULT hr;
	ID3DBlob* pErrorCode = nullptr;
	// 정점 셰이더 컴파일
	hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);

	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}
	// 정점 셰이더 생성
	hr = m_pd3dDevice->CreateVertexShader(m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), NULL, &m_pVS);

	// 픽셀 셰이더 컴파일
	hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);
	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}
	// 픽셀 셰이더 생성
	hr = m_pd3dDevice->CreatePixelShader(m_pPSCode->GetBufferPointer(), m_pPSCode->GetBufferSize(), NULL, &m_pPS);

	return hr;
}

HRESULT Base_object::CreateVertexLayout() {
	
	HRESULT hr;

	// 정점 레이아웃 생성하기 color는 xyz 이후 데이터부터 시작이니 12바이트가 시작점(float 1개 = 4byte)
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT num_element = sizeof(ied) / sizeof(ied[0]);
	hr = m_pd3dDevice->CreateInputLayout(ied, num_element, m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), &m_pVertexLayout);

	return hr;
}



bool Base_object::Render() {
	
	// gpu update 필요
	m_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, 0, NULL,
		&m_VertexList.at(0), 0, 0);


	// 삼각형 렌더링
	UINT stride = sizeof(SimpleVertex); // 정점 1개 size(byte)
	UINT offset = 0;					// 정점 버퍼에서 출발 지점 (byte)

	// 새롭게 생성하는 것 아니니까 context로
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
	m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
	// texture
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
	m_pImmediateContext->Draw(m_VertexList.size(), 0);

	return true;
}



bool Base_object::Release() {

	if (m_Texture) m_Texture->Release();
	if (m_pTextureSRV) m_pTextureSRV->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVS) m_pVS->Release();
	if (m_pPS) m_pPS->Release();
	if (m_pVSCode) m_pVSCode->Release();
	if (m_pPSCode) m_pPSCode->Release();

	return true;
}
