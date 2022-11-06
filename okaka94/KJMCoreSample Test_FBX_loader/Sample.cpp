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

	Main_cam = new Camera_debug;
	Main_cam->Create_View_matrix(Vector(0, 6, -50), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam->Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	
	return true;
}
bool Sample::Frame()
{
	Main_cam->Frame();
	for (auto fbx : m_fbx_list)
	{
		fbx->Frame();
	}


	return true;
}
bool Sample::Render()
{
	for (int iModel = 0; iModel < m_fbx_list.size(); iModel++)
	{
		for (int iObj = 0; iObj < m_fbx_list[iModel]->m_Draw_list.size(); iObj++)
		{
			Matrix matWorld;
			matWorld._41 = 100 * iModel;
			m_fbx_list[iModel]->m_Draw_list[iObj]->SetMatrix(&matWorld,
				&Main_cam->m_View_matrix,
				&Main_cam->m_Proj_matrix);
			m_fbx_list[iModel]->m_Draw_list[iObj]->Render();
		}
	}
	

	return true;
}
bool Sample::Release()
{
	
	for (auto fbx : m_fbx_list)
	{
		fbx->Release();
	}
	if (Main_cam) {
		Main_cam->Release();
		delete Main_cam;
	}
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}