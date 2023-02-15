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

	// 기본 fbx가 0번에 오도록 (메시정보 없는 fbx 로드 안되도록 예외처리하기)

	FBX_loader* Chell = new FBX_loader;
	if (Chell->Init())
	{
		Chell->Load("../../data/fbx/Chell.fbx");
	}
	m_fbx_table.insert(std::make_pair(L"Chell", _actionIdx++));
	m_fbx_list.push_back(Chell);


	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"Skinning.txt";

	for (auto fbx : m_fbx_list)
	{
		for (int iObj = 0; iObj < fbx->_drawList.size(); iObj++)
		{
			FBX_obj* pObj = fbx->_drawList[iObj];
			std::wstring  szLoad = szDefaultDir + pObj->m_Texture_name;
			pObj->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename, szLoad);
		}
	}


	User_char = new FBX_char;
	User_char->m_FBX_loader = m_fbx_list[0];
	User_char->CreateConstantBuffer(m_pd3dDevice.Get());


	User_char->m_Anim_scene = User_char->m_FBX_loader->_animScene;
	Action_table action;
	action.Start_frame = User_char->m_Anim_scene.Start_frame;
	action.End_frame = User_char->m_Anim_scene.End_frame;
	action.Loop_state = true;
	User_char->m_Action_map.insert(std::make_pair(L"default", action));
	User_char->m_Current_action = User_char->m_Action_map.find(L"default")->second;



	// Animation 추가

	FBX_loader* Idle = new FBX_loader;
	if (Idle->Init())
	{
		if (Idle->Load("../../data/fbx/Chell@Idle.fbx"))
		{
			Idle->CreateConstantBuffer(m_pd3dDevice.Get());
			m_fbx_table.insert(std::make_pair(L"Idle", _actionIdx++));
			m_fbx_list.push_back(Idle);
			User_char->m_FBX_action_list.insert(std::make_pair(L"Idle", Idle));
		}
	}

	FBX_loader* Jump = new FBX_loader;
	if (Jump->Init())
	{
		if (Jump->Load("../../data/fbx/Chell@Jump.fbx"))
		{
			Jump->CreateConstantBuffer(m_pd3dDevice.Get());
			m_fbx_table.insert(std::make_pair(L"Jump", _actionIdx++));
			m_fbx_list.push_back(Jump);
			User_char->m_FBX_action_list.insert(std::make_pair(L"Jump", Jump));
		}
	}
	

	FBX_loader* RunN = new FBX_loader;
	if (RunN->Init())
	{
		if (RunN->Load("../../data/fbx/Chell@RunN.fbx"))
		{
			RunN->CreateConstantBuffer(m_pd3dDevice.Get());
			m_fbx_table.insert(std::make_pair(L"RunN", _actionIdx++));
			m_fbx_list.push_back(RunN);
			User_char->m_FBX_action_list.insert(std::make_pair(L"RunN", RunN));
		}
	}
	_actionIdx = 1;

	Main_cam = new Camera_debug;
	Main_cam->Create_View_matrix(Vector(0, 100, -100), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam->Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	return true;
}
bool Sample::Frame()
{

	// ImGui Frame()
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();



	// ImGui UI Creation
	ImGui::SetNextWindowSize(ImVec2(300, 150));
	if (ImGui::Begin("Anim Selector", NULL)) 
	{
		if (ImGui::Button("Next")) 
		{
			_actionIdx = _actionIdx == m_fbx_list.size() ? 0 : _actionIdx;
			User_char->m_FBX_action = m_fbx_list[_actionIdx++];

			if (User_char->m_FBX_action)
			{
				User_char->m_Anim_frame = 0;
				User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
				User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
				User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Replay")) {
			if (User_char->m_FBX_action) {
				User_char->m_Anim_frame = 0;
				User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
				User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
				User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
			}
			
		}
		ImGui::SameLine();
		if (ImGui::Button("Play")) {
			if (User_char->m_FBX_action) {
				User_char->m_Anim_scene.Frame_speed = 30.0f;
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Pause")) {
			if (User_char->m_FBX_action) {
				User_char->m_Anim_scene.Frame_speed = 0.0f;
			}

		}

		// 프레임 슬라이더
		if (ImGui::DragFloat("##currentFrame", &User_char->m_Anim_frame , 0.1f , User_char->m_Current_action.Start_frame, User_char->m_Current_action.End_frame)) {
			if (User_char->m_FBX_action) {
				User_char->m_Anim_scene.Frame_speed = 0.0f;
			}
		}ImGui::SameLine();
		ImGui::Text("Frame");	ImGui::SameLine();
		ImGui::InputFloat("Frame##inputfloat", &User_char->m_Anim_frame);
		
	}ImGui::End();
	
	
	//  애니메이션 생성 버튼 만들기
	ImGui::SetNextWindowSize(ImVec2(600, 150));

	
	if (ImGui::Begin(User_char->m_FBX_loader->_fileName.c_str(),NULL))
	{
		static bool loop= true;
		if (User_char->m_FBX_action) {
			ImGui::Text("Current Animation : ");	ImGui::SameLine();
			ImGui::Text(User_char->m_FBX_action->_fileName.c_str());						// 현재 애니메이션
		}
		ImGui::Text("Current Frame : %f", User_char->m_Anim_frame);							// 현재 프레임
		ImGui::Text("Start : %d", User_char->m_Current_action.Start_frame);					// 시작 프레임
		ImGui::SameLine();
		ImGui::Text("End : %d", User_char->m_Current_action.End_frame);						// 끝 프레임
		ImGui::Checkbox("Loop", &loop);														// 루프 버튼
		User_char->m_Current_action.Loop_state = loop;
		
		

	}ImGui::End();



	ClearD3D11DeviceContext(m_pImmediateContext.Get());
	Main_cam->Frame();



	User_char->Update_anim(m_pImmediateContext.Get());




	return true;
}
bool Sample::Render()
{

	User_char->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
	User_char->Render(m_pImmediateContext.Get());

	//std::wstring frame = L"Anim_frame : ";
	//frame += std::to_wstring(User_char->m_Anim_frame);
	//Writer::GetInstance().m_szDefaultText = frame;


	
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

	User_char->Release();
	delete User_char;

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"Test", 800, 600);

	demo.Run();

	return 1;
}