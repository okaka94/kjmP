#include "Shader.h"

bool	Shader::Init() {
	return true;
}
bool	Shader::Frame() {
	return true;
}
bool	Shader::Render() {
	return true;
}
bool	Shader::Release() {

	if (m_pVS) m_pVS->Release();
	if (m_pPS) m_pPS->Release();
	if (m_pVSCode) m_pVSCode->Release();
	if (m_pPSCode) m_pPSCode->Release();

	m_pVS = nullptr;
	m_pPS = nullptr;
	m_pVSCode = nullptr;
	m_pPSCode = nullptr;

	return true;
}

HRESULT Shader::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediate, std::wstring name) {
	HRESULT hr;
	m_pd3dDevice = pd3dDevice;
	m_pImmediateContext = pImmediate;

	DWORD dwShaderFlags = D3DCOMPILE_SKIP_OPTIMIZATION;
#if defined( _DEBUG ) 
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorCode = nullptr;
	// Á¤Á¡ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
	hr = D3DCompileFromFile(name.c_str(), NULL, NULL, "VS", "vs_5_0", dwShaderFlags, 0, &m_pVSCode, &pErrorCode);

	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}
	// Á¤Á¡ ¼ÎÀÌ´õ »ý¼º
	hr = m_pd3dDevice->CreateVertexShader(m_pVSCode->GetBufferPointer(), m_pVSCode->GetBufferSize(), NULL, &m_pVS);

	// ÇÈ¼¿ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
	hr = D3DCompileFromFile(name.c_str(), NULL, NULL, "PS", "ps_5_0", dwShaderFlags, 0, &m_pPSCode, &pErrorCode);
	if (FAILED(hr)) {
		if (pErrorCode) {
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}
	// ÇÈ¼¿ ¼ÎÀÌ´õ »ý¼º
	hr = m_pd3dDevice->CreatePixelShader(m_pPSCode->GetBufferPointer(), m_pPSCode->GetBufferSize(), NULL, &m_pPS);

	return hr;

}
