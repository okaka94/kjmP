#include "Base_object.h"
#include "Shader_manager.h"
#include "Texture_manager.h"

bool Base_object::Init() { return true; }
bool Base_object::Frame() { 
	// gpu update 
	m_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, 0, NULL,
		&m_VertexList.at(0), 0, 0);

	return true; 
}


bool Base_object::Create(ID3D11Device* pd3dDevice , ID3D11DeviceContext* pImmediateContext , const wchar_t* shaderName, const wchar_t* texName) {
	SetDevice(pd3dDevice, pImmediateContext);

	if (FAILED(CreateVertexBuffer()))
		return false;

	//if (FAILED(CreateShader(shaderName)))			// 리턴값이 bool인데 굳이 매크로 사용?
	//	return false;
	if (!CreateShader(shaderName))
		return false;

	if (FAILED(CreateVertexLayout()))
		return false;

	if (!LoadTexture(texName))
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
	m_VertexList[0].p = { -1.0f,  1.0f, 0.0f };
	m_VertexList[0].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[0].t = { 0.0f,0.0f };

	m_VertexList[1].p = { 1.0f,  1.0f, 0.0f };
	m_VertexList[1].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[1].t = { 1.0f,0.0f };

	m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
	m_VertexList[2].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[2].t = { 0.0f,1.0f };

	m_VertexList[3].p = { -1.0f, -1.0f, 0.0f };
	m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[3].t = { 0.0f,1.0f };

	m_VertexList[4].p = { 1.0f,  1.0f, 0.0f };
	m_VertexList[4].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[4].t = { 1.0f,0.0f };

	m_VertexList[5].p = { 1.0f, -1.0f, 0.0f };
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

bool	Base_object::CreateShader(std::wstring filename) {
	
	m_pShader = Shader_manager::GetInstance().Load(filename);

	if (m_pShader) return true;


	return false;
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
	hr = m_pd3dDevice->CreateInputLayout(ied, num_element, m_pShader->m_pVSCode->GetBufferPointer(), m_pShader->m_pVSCode->GetBufferSize(), &m_pVertexLayout);

	return hr;
}

bool	Base_object::LoadTexture(std::wstring filename) {

	m_pTexture = Texture_manager::GetInstance().Load(filename);

	if (m_pTexture) return true;


	return false;
}


bool Base_object::Pre_Render() {

	// 삼각형 렌더링
	UINT stride = sizeof(SimpleVertex); // 정점 1개 size(byte)
	UINT offset = 0;					// 정점 버퍼에서 출발 지점 (byte)

	// 새롭게 생성하는 것 아니니까 context로
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
	m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);
	// texture
	ID3D11ShaderResourceView* SRV = m_pTexture->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(0, 1,  &SRV);
	

	return true;
}

bool Base_object::Render() {

	Pre_Render();
	Post_Render();
	return true;
}

bool Base_object::Post_Render() {

	m_pImmediateContext->Draw(m_VertexList.size(), 0);   //  Draw 하기 전까지 SetShader 등의 순서는 무관함, 세팅된 것들을 Draw 호출할 때 그래픽 파이프라인으로 넘김

	return true;
}


bool Base_object::Release() {

	m_pTexture->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	m_pShader->Release();

	return true;
}
