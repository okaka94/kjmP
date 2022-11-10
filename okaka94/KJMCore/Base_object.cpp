#include "Base_object.h"


bool Base_object::Init() { return true; }
bool Base_object::Frame() { 
	// gpu update 
	//m_pImmediateContext->UpdateSubresource(
	//	m_pVertexBuffer, 0, NULL,
	//	&m_VertexList.at(0), 0, 0);

	return true; 
}




bool Base_object::Create(ID3D11Device* pd3dDevice , ID3D11DeviceContext* pImmediateContext , const wchar_t* shaderName, const wchar_t* texName) {
	SetDevice(pd3dDevice, pImmediateContext);
	m_Shader_name = shaderName;
	m_Texture_name = texName;

	if (FAILED(CreateConstantBuffer()))
		return false;
	
	if (FAILED(CreateVertexBuffer()))
		return false;

	if (FAILED(CreateIndexBuffer()))
		return false;

	if (!CreateShader(shaderName))
		return false;

	if (FAILED(CreateVertexLayout()))
		return false;

	if (!LoadTexture(texName))
		return false;

}

bool Base_object::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderName, std::wstring texName) {
	SetDevice(pd3dDevice, pImmediateContext);
	m_Shader_name = shaderName;
	m_Texture_name = texName;

	if (FAILED(CreateConstantBuffer()))
		return false;

	if (FAILED(CreateVertexBuffer()))
		return false;

	if (FAILED(CreateIndexBuffer()))
		return false;

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

void Base_object::CreateConstantData()
{
	m_cbData.World_matrix.Set_I_matrix();
	m_cbData.View_matrix.Set_I_matrix();
	m_cbData.Proj_matrix.Set_I_matrix();
	m_cbData.g_Color = { 1.0f,1.0f,1.0f,1.0f };
	m_cbData.World_matrix.Return_T_matrix();
	m_cbData.View_matrix.Return_T_matrix();
	m_cbData.Proj_matrix.Return_T_matrix();  // 단위행렬이라 전치해도 똑같은 것 같음(?)
}

HRESULT Base_object::CreateConstantBuffer()
{
	HRESULT hr;
	CreateConstantData();
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER) * 1; // 바이트 용량
	// GPU 메모리에 할당
	bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_cbData;
	hr = m_pd3dDevice->CreateBuffer(
		&bd, // 버퍼 할당
		&sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
		&m_pConstantBuffer);
	return hr;
}

void Base_object::CreateVertexList() {
	if (m_VertexList.size() > 0)
	{
		m_InitVertexList = m_VertexList;
		return;
	}

	m_VertexList.resize(4);

	m_VertexList[0].p = { -1.0f,  1.0f, 0.0f };
	m_VertexList[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VertexList[0].t = { 0.0f,0.0f };

	m_VertexList[1].p = { 1.0f,  1.0f, 0.0f };
	m_VertexList[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VertexList[1].t = { 1.0f,0.0f };

	m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
	m_VertexList[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VertexList[2].t = { 0.0f,1.0f };

	
	m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };
	m_VertexList[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_VertexList[3].t = { 1.0f,1.0f };

	m_InitVertexList = m_VertexList;
}

void Base_object::CreateIndexList() {
	if (m_IndexList.size() > 0)return;

	m_IndexList.resize(6);

	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 2;
	m_IndexList[4] = 1;
	m_IndexList[5] = 3;

}

ID3D11Buffer* Base_object::ReturnVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT iNumVertex, UINT iVertexSize) {

	HRESULT hr;
	ID3D11Buffer* pVB = nullptr;
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = iVertexSize * iNumVertex; // 바이트 용량
	// GPU 메모리에 할당
	bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = pDataAddress;
	hr = pd3dDevice->CreateBuffer(
		&bd, // 버퍼 할당
		&sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
		&pVB);
	return pVB;

}


HRESULT Base_object::CreateVertexBuffer() {

	HRESULT hr;
	CreateVertexList();
	int num_vertex = m_VertexList.size();
	D3D11_BUFFER_DESC	bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(PNCTVertex) * num_vertex;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_VertexList.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	return hr;
}

HRESULT Base_object::CreateIndexBuffer() {

	HRESULT hr;
	CreateIndexList();
	int num_vertex = m_IndexList.size();
	D3D11_BUFFER_DESC	bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * num_vertex;
	bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_IndexList.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);

	return hr;
}

bool	Base_object::CreateShader(std::wstring filename) {
	
	m_pShader = Shader_manager::GetInstance().Load(filename);

	if (m_pShader) {
		m_pVS = m_pShader->m_pVS;
		m_pPS = m_pShader->m_pPS;
		m_pVSCode = m_pShader->m_pVSCode;
		return true;
	}
		


	return false;
}

HRESULT Base_object::CreateVertexLayout() {
	
	HRESULT hr;

	// 정점 레이아웃 생성하기 color는 xyz 이후 데이터부터 시작이니 12바이트가 시작점(float 1개 = 4byte)
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT num_element = sizeof(ied) / sizeof(ied[0]);
	hr = m_pd3dDevice->CreateInputLayout(ied, num_element, m_pVSCode->GetBufferPointer(),m_pVSCode->GetBufferSize(), &m_pVertexLayout);

	return hr;
}

bool	Base_object::LoadTexture(std::wstring filename) {

	m_pTexture = Texture_manager::GetInstance().Load(filename);

	if (m_pTexture != nullptr) {
		m_pTextureSRV = m_pTexture->Get_SRV();
	}
	
		return true;


	return false;
}


bool Base_object::Pre_Render() {

	// 삼각형 렌더링
	

	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
	m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);
	UINT stride = sizeof(PNCTVertex); // 정점 1개 size(byte)
	UINT offset = 0;					// 정점 버퍼에서 출발 지점 (byte)
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);	
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);


	
	
	return true;
}

bool Base_object::Render() {

	Pre_Render();
	Post_Render();
	return true;
}

bool Base_object::Post_Render() {

	if (m_pIndexBuffer == nullptr)
		m_pImmediateContext->Draw(m_VertexList.size(), 0);   //  Draw 하기 전까지 SetShader 등의 순서는 무관함, 세팅된 것들을 Draw 호출할 때 그래픽 파이프라인으로 넘김
	else
		m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);

	return true;
}


bool Base_object::Release() {

	//m_pTexture->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	if (m_pConstantBuffer) m_pConstantBuffer->Release();
	//m_pShader->Release();

	return true;
}

void   Base_object::UpdateVertexBuffer()
{
	m_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, 0, nullptr,
		&m_VertexList.at(0), 0, 0);
}

void   Base_object::UpdateConstantBuffer()
{
	m_cbData.World_matrix = m_World_matrix.Return_T_matrix();
	m_cbData.View_matrix = m_View_matrix.Return_T_matrix();
	m_cbData.Proj_matrix = m_Proj_matrix.Return_T_matrix();
	m_pImmediateContext->UpdateSubresource(
		m_pConstantBuffer, 0, nullptr,
		&m_cbData, 0, 0);
}

void	Base_object::SetMatrix(Matrix* World, Matrix* View, Matrix* Proj)
{
	if (World != nullptr)
	{
		m_World_matrix = *World;
	}
	if (View != nullptr)
	{
		m_View_matrix = *View;
	}
	if (Proj != nullptr)
	{
		m_Proj_matrix = *Proj;
	}
	UpdateConstantBuffer();
}