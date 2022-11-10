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
		
	FBX_loader* Turret = new FBX_loader;
	if (Turret->Init())
	{
		Turret->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");
		
	}
	m_fbx_list.push_back(Turret);

	//FBX_loader* Man = new FBX_loader;
	//if (Man->Init())
	//{
	//	Man->Load("../../data/fbx/Man.FBX");

	//}
	//m_fbx_list.push_back(Man);


	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"../../data/shader/DefaultShape_PNCT.txt";

	for (auto fbx : m_fbx_list)
	{
		for (int iObj = 0; iObj < fbx->m_Draw_list.size(); iObj++)
		{
			FBX_obj* pObj = fbx->m_Draw_list[iObj];
			std::wstring  szLoad = szDefaultDir + pObj->m_Texture_name;
			pObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename, szLoad);
		}
	}

	Main_cam = new Camera_debug;
	Main_cam->Create_View_matrix(Vector(0, 1, -20), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam->Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	
	return true;
}
bool Sample::Frame()
{
	ClearD3D11DeviceContext(m_pImmediateContext.Get());
	Main_cam->Frame();

	for (auto fbx : m_fbx_list)
	{
		fbx->Update_anim(m_pImmediateContext.Get());
	}


	return true;
}
bool Sample::Render()
{
	
	for (int file = 0; file < m_fbx_list.size(); file++) {
		for (int obj = 0; obj < m_fbx_list[file]->m_Draw_list.size(); obj++) {
			//FBX_obj* fbx_obj = m_fbx_list[file]->m_Draw_list[obj];	// file의 draw_list에 있는 fbx_obj 할당
			//fbx_obj->m_Anim_frame += g_fSecPerFrame *0.3f * fbx_obj->m_Anim_scene.Frame_speed * fbx_obj->m_Anim_inverse;
			//if (fbx_obj->m_Anim_frame > fbx_obj->m_Anim_scene.End_frame || fbx_obj->m_Anim_frame < fbx_obj->m_Anim_scene.Start_frame) {
			//	fbx_obj->m_Anim_frame = min(fbx_obj->m_Anim_frame, fbx_obj->m_Anim_scene.End_frame);
			//	fbx_obj->m_Anim_frame = max(fbx_obj->m_Anim_frame, fbx_obj->m_Anim_scene.Start_frame);
			//	fbx_obj->m_Anim_inverse *= -1.0f;
			//}
			//fbx_obj->m_obj_Anim_matrix = fbx_obj->Interpolate(fbx_obj->m_Anim_frame);
			//		//fbx_obj->m_obj_Anim_matrix = fbx_obj->m_Anim_track_list[fbx_obj->m_Anim_frame].Anim_matrix;
			FBX_obj* fbx_obj = m_fbx_list[file]->m_Draw_list[obj];
			fbx_obj->m_World_matrix = fbx_obj->m_obj_Anim_matrix;
			fbx_obj->SetMatrix(&fbx_obj->m_World_matrix, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
			fbx_obj->Render();
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