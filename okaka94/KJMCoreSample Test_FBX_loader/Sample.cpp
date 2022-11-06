#include "Sample.h"

bool Sample::Init()
{
		
	FBX_loader* Loader = new FBX_loader;
	if (Loader->Init())
	{
		Loader->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");
	}
	m_fbx_list.push_back(Loader);

	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"../../data/shader/DefaultShape_PNCT.txt";

	for (auto fbx : m_fbx_list)
	{
		for (int iObj = 0; iObj < fbx->m_Draw_list.size(); iObj++)
		{
			FBX_obj* pObj = fbx->m_Draw_list[iObj];
			std::wstring  szLoad = szDefaultDir + pObj->m_Texture_name;
			pObj->Create(m_pd3dDevice, m_pImmediateContext, shaderfilename, szLoad);
		}
	}

	m_pMainCamera = new TCameraDebug;
	m_pMainCamera->CreateViewMatrix(TVector3(0, 6, -50), TVector3(0, 0, 0), TVector3(0, 1, 0));
	m_pMainCamera->CreateProjMatrix(1.0f, 10000.0f, T_PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);

	return true;
}
bool Sample::Frame()
{
		


	return true;
}
bool Sample::Render()
{
	
	

	return true;
}
bool Sample::Release()
{
	

	

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}