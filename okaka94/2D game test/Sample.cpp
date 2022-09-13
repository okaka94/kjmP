#include "Sample.h"



bool Sample::Init()
{
	Texture* MaskTex = Texture_manager::GetInstance().Load(L"../../data/EBA/Note_mask.png");
	ex = new Note;
	ex->Create(m_pd3dDevice, m_pImmediateContext, 
		L"../../data/shader/DefaultShape_Mask.txt",L"../../data/EBA/Note.png");
	ex->Set_rect(6,6);
	ex->Set_position({ 100,100 });
	ex->Set_mask(MaskTex);

	return true;
}
bool Sample::Frame()
{
	ex->Frame();
	return true;
}
bool Sample::Render()
{
	ex->Render();
	ID3D11ShaderResourceView* SRV = ex->m_pMasktex->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	
	return true;
}
bool Sample::Release()
{
	ex->Release();
	delete ex;
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}