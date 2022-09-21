#include "Base_object.h"


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

void Base_object::CreateVertexList() {

	m_VertexList.resize(4);

	m_VertexList[0].p = { -1.0f,  1.0f, 0.0f };
	m_VertexList[0].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[0].t = { 0.0f,0.0f };

	m_VertexList[1].p = { 1.0f,  1.0f, 0.0f };
	m_VertexList[1].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[1].t = { 1.0f,0.0f };

	m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
	m_VertexList[2].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[2].t = { 0.0f,1.0f };

	
	m_VertexList[3].p = { 1.0f, -1.0f, 0.0f };
	m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_VertexList[3].t = { 1.0f,1.0f };

}

void Base_object::CreateIndexList() {

	m_IndexList.resize(6);

	m_IndexList[0] = 0;
	m_IndexList[1] = 1;
	m_IndexList[2] = 2;
	m_IndexList[3] = 2;
	m_IndexList[4] = 1;
	m_IndexList[5] = 3;

}

HRESULT Base_object::CreateVertexBuffer() {

	HRESULT hr;
	CreateVertexList();
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

HRESULT Base_object::CreateIndexBuffer() {

	HRESULT hr;
	CreateIndexList();
	int num_vertex = m_IndexList.size();
	D3D11_BUFFER_DESC	bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * num_vertex;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_IndexList.at(0);
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);

	return hr;
}

bool	Base_object::CreateShader(std::wstring filename) {
	
	m_pShader = Shader_manager::GetInstance().Load(filename);

	if (m_pShader) return true;


	return false;
}

HRESULT Base_object::CreateVertexLayout() {
	
	HRESULT hr;

	// ���� ���̾ƿ� �����ϱ� color�� xyz ���� �����ͺ��� �����̴� 12����Ʈ�� ������(float 1�� = 4byte)
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

	if (m_pTexture) 
		return true;


	return false;
}


bool Base_object::Pre_Render() {

	// �ﰢ�� ������
	UINT stride = sizeof(SimpleVertex); // ���� 1�� size(byte)
	UINT offset = 0;					// ���� ���ۿ��� ��� ���� (byte)

	// ���Ӱ� �����ϴ� �� �ƴϴϱ� context��
	m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
	m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);
	// texture
	ID3D11ShaderResourceView* SRV = m_pTexture->Get_SRV();
	m_pTexture->Apply(m_pImmediateContext, 0);
	
	return true;
}

bool Base_object::Render() {

	Pre_Render();
	Post_Render();
	return true;
}

bool Base_object::Post_Render() {

	if (m_pIndexBuffer == nullptr)
		m_pImmediateContext->Draw(m_VertexList.size(), 0);   //  Draw �ϱ� ������ SetShader ���� ������ ������, ���õ� �͵��� Draw ȣ���� �� �׷��� �������������� �ѱ�
	else
		m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);

	return true;
}


bool Base_object::Release() {

	//m_pTexture->Release();
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pIndexBuffer) m_pIndexBuffer->Release();
	if (m_pVertexLayout) m_pVertexLayout->Release();
	//m_pShader->Release();

	return true;
}
