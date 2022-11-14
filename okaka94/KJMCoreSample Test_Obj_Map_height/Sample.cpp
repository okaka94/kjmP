#include "Sample.h"
void Sample::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	// Unbind all objects from the immediate context
	if (pd3dDeviceContext == NULL) return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Shaders
	//pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

	//// IA clear
	//pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
	//pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
	//pd3dDeviceContext->IASetInputLayout(NULL);

	//// Constant buffers
	//pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

	// Resources
	pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

	//// Samplers
	//pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

	//// Render targets
	//pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

	//// States
	//FLOAT blendFactor[4] = { 0,0,0,0 };
	//pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
	//pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
	//pd3dDeviceContext->RSSetState(NULL);
}

bool Sample::Init()
{
	
	UINT fbx_idx = 0;

	//FBX_loader* Man = new FBX_loader;
	//if (Man->Init())
	//{
	//	if (Man->Load("../../data/fbx/Man.FBX")) {
	//		Man->CreateConstantBuffer(m_pd3dDevice.Get());
	//	}

	//}
	//m_fbx_table.insert(std::make_pair(L"Man", fbx_idx++));
	//m_fbx_list.push_back(Man);

	FBX_loader* Swat_turn = new FBX_loader;
	if (Swat_turn->Init())
	{
		if (Swat_turn->Load("../../data/fbx/Swat@turning_right_45_degrees.fbx"))
		{
			Swat_turn->CreateConstantBuffer(m_pd3dDevice.Get());
		}
	}
	m_fbx_table.insert(std::make_pair(L"Swat_turn", fbx_idx++));
	m_fbx_list.push_back(Swat_turn);

	FBX_loader* Swat = new FBX_loader;
	if (Swat->Init())
	{
		Swat->Load("../../data/fbx/Swat.fbx");
	}
	m_fbx_table.insert(std::make_pair(L"Swat", fbx_idx++));
	m_fbx_list.push_back(Swat);


	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"Skinning.txt";

	for (auto fbx : m_fbx_list)
	{
		for (int iObj = 0; iObj < fbx->m_Draw_list.size(); iObj++)
		{
			FBX_obj* pObj = fbx->m_Draw_list[iObj];
			std::wstring  szLoad = szDefaultDir + pObj->m_Texture_name;
			pObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename, szLoad);
		}
	}
	




	//for (int iObj = 0; iObj < 5; iObj++)
	//{
	//	FBX_char* pNpc = new FBX_char;
	//	
	//	FBX_INDEX = m_fbx_table.find(L"Man")->second;
	//	pNpc->m_FBX_loader = m_fbx_list[FBX_INDEX];
	//	pNpc->m_World_matrix._41 = -4.0f + iObj * 2;
	//	pNpc->m_Anim_scene = pNpc->m_FBX_loader->m_Anim_scene;
	//	pNpc->CreateConstantBuffer(m_pd3dDevice.Get());
	//	Action_table action;
	//	action.Start_frame = 61;
	//	action.End_frame = 91;
	//	action.Loop_state = true;
	//	pNpc->m_Action_map.insert(std::make_pair(L"walk", action));
	//	pNpc->m_Current_action = pNpc->m_Action_map.find(L"walk")->second;

	//	m_NpcList.push_back(pNpc);
	//}



	Main_cam = new Camera_debug;
	//Main_cam->Create_View_matrix(Vector(0, 20, -20), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam->Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);


	BG = new Map;
	BG->Load_height_map(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/map/heightMap513.bmp");
	BG->Build(m_pd3dDevice.Get(), BG->cols_num, BG->rows_num, Main_cam);
	BG->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShape_PNCT.txt", L"../../data/NormalMap/stone_wall.bmp");
	BG->Create_Qtree(m_pd3dDevice.Get(), Main_cam);

	UINT FBX_INDEX = 0;


	User_char = new FBX_char;
	FBX_INDEX = m_fbx_table.find(L"Swat")->second;
	User_char->m_FBX_loader = m_fbx_list[FBX_INDEX];
	FBX_INDEX = m_fbx_table.find(L"Swat_turn")->second;
	User_char->m_FBX_action = m_fbx_list[FBX_INDEX];

	User_char->m_World_matrix._42 = BG->Get_height(0, 0);

	User_char->CreateConstantBuffer(m_pd3dDevice.Get());

	if (User_char->m_FBX_action)
	{
		User_char->m_Anim_scene = User_char->m_FBX_action->m_Anim_scene;
		User_char->m_FBX_action_list.insert(std::make_pair(L"walking", User_char->m_FBX_action));
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->m_Anim_scene.Start_frame;
		User_char->m_Current_action.End_frame = 50;// pFbxLoaderA->m_AnimScene.iEndFrame;
	}
	else
	{
		User_char->m_Anim_scene = User_char->m_FBX_loader->m_Anim_scene;
		Action_table action;
		action.Start_frame = User_char->m_Anim_scene.Start_frame;
		action.End_frame = User_char->m_Anim_scene.End_frame;
		action.Loop_state = true;
		User_char->m_Action_map.insert(std::make_pair(L"idle", action));
	}
	
	Main_cam->Create_View_matrix(Vector(0, 50, -20), Vector(0, BG->Get_height(0, 0), 0), Vector(0, 1, 0));
	
	return true;
}
bool Sample::Frame()
{
	ClearD3D11DeviceContext(m_pImmediateContext.Get());
	//Main_cam->Frame();

	/*for (auto npc : m_NpcList)
	{
		npc->Update_anim(m_pImmediateContext.Get());
	}*/

	User_char->Update_anim(m_pImmediateContext.Get());

	return true;
}
bool Sample::Render()
{

	/*for (int iNpc = 0; iNpc < m_NpcList.size(); iNpc++)
	{
		m_NpcList[iNpc]->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
		m_NpcList[iNpc]->Render(m_pImmediateContext.Get());
	}*/

	User_char->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
	User_char->Render(m_pImmediateContext.Get());

	BG->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
	BG->Render();

	return true;
}
bool Sample::Release()
{
	
	for (auto fbx : m_fbx_list)
	{
		fbx->Release();
	}

	//for (auto npc : m_NpcList)
	//{
	//	npc->Release();
	//	delete npc;
	//}

	if (Main_cam) {
		Main_cam->Release();
		delete Main_cam;
	}

	User_char->Release();
	delete User_char;

	BG->Release();
	delete BG;

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}