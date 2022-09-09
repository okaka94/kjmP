#include "Sample.h"

HRESULT Sample::CreateVertexBuffer() {
	HRESULT hr;

	SimpleVertex vertices[] = {
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,		// V0
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,		// V1
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,		// V2 (시계방향으로)
	};
	int num_vertex = sizeof(vertices) / sizeof(vertices[0]);
	D3D11_BUFFER_DESC	bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(SimpleVertex) * num_vertex;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertices;
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	return hr;
}

HRESULT Sample::CreateVertexLayout() {
	HRESULT hr;
	ID3DBlob* pErrorCode = nullptr;
	// 정점 셰이더 컴파일
	hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "main", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);

	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return false;
	}
	// 정점 셰이더 생성
	hr = m_pd3dDevice->CreateVertexShader(m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), NULL, &m_pVS);

	// 픽셀 셰이더 컴파일
	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PSMain", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);
	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return false;
	}
	// 픽셀 셰이더 생성
	hr = m_pd3dDevice->CreatePixelShader(m_pPSCode->GetBufferPointer(), m_pPSCode->GetBufferSize(), NULL, &m_pPS);
	
	// 정점 레이아웃 생성하기 color는 xyz 이후 데이터부터 시작이니 12바이트가 시작점(float 1개 = 4byte)
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	UINT num_element = sizeof(ied) / sizeof(ied[0]);
	hr = m_pd3dDevice->CreateInputLayout(ied, num_element, m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), &m_pVertexLayout);
	
	return hr;
}


Sample::Sample() {
}
Sample::~Sample() {
}

bool Sample::Init() {
	if (FAILED(CreateVertexBuffer()))
		return false;

	if (FAILED(CreateVertexLayout()))
		return false;

	return true;
}

bool Sample::Frame() {
	
	return true;
}

bool Sample::Render() {
	
	// 삼각형 렌더링
	UINT stride = sizeof(SimpleVertex); // 정점 1개 size(byte)
	UINT offset = 0;					// 정점 버퍼에서 출발 지점 (byte)

	// 새롭게 생성하는 것 아니니까 context로
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
	m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);

	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->Draw(3, 0);

	return true;
}

bool Sample::Release() {
	
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pVS) m_pVS->Release();
	if (m_pPS) m_pPS->Release();
	if (m_pVSCode) m_pVSCode->Release();
	if (m_pPSCode) m_pPSCode->Release();

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample demo;
	demo.SetWindow(hinstance, L"okaka_window");
	demo.Run();


	

	return 1;
}