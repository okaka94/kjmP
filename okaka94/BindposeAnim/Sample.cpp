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
	_fileDlg.SetTypeFilters({ ".fbx" });	// type filter

	

	// Movement Animation
	FBX_loader* idle = new FBX_loader;
	if (idle->Init())
	{
		idle->Load("../../data/fbx/Chell@Idle.fbx");
		idle->CreateConstantBuffer(m_pd3dDevice.Get());
		m_fbx_table.insert(std::make_pair('0', idle));
	}

	FBX_loader* moveForward = new FBX_loader;
	if (moveForward->Init())
	{
		moveForward->Load("../../data/fbx/Chell@RunN.fbx");
		moveForward->CreateConstantBuffer(m_pd3dDevice.Get());
		m_fbx_table.insert(std::make_pair('W', moveForward));
	}

	FBX_loader* moveBackward = new FBX_loader;
	if (moveBackward->Init())
	{
		moveBackward->Load("../../data/fbx/Chell@RunS.fbx");
		moveBackward->CreateConstantBuffer(m_pd3dDevice.Get());
		m_fbx_table.insert(std::make_pair('S', moveBackward));
	}

	FBX_loader* moveRight = new FBX_loader;
	if (moveRight->Init())
	{
		moveRight->Load("../../data/fbx/Chell@RunW.fbx");
		moveRight->CreateConstantBuffer(m_pd3dDevice.Get());
		m_fbx_table.insert(std::make_pair('D', moveRight));
	}

	FBX_loader* moveLeft = new FBX_loader;
	if (moveLeft->Init())
	{
		moveLeft->Load("../../data/fbx/Chell@RunE.fbx");
		moveLeft->CreateConstantBuffer(m_pd3dDevice.Get());
		m_fbx_table.insert(std::make_pair('A', moveLeft));
	}

	

	Main_cam = new Camera_debug;
	//Main_cam->Create_View_matrix(Vector(0, 100, -100), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam->Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);


	BG = new Map;
	//BG->Load_height_map(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/map/Map512.png");
	BG->Load_height_map(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/map/HEIGHT_TEMPLE.bmp");
	BG->Build(m_pd3dDevice.Get(), BG->cols_num, BG->rows_num, Main_cam);
	BG->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShape_PNCT.txt", L"../../data/NormalMap/stone_wall.bmp");
	BG->Create_Qtree(m_pd3dDevice.Get(), Main_cam);
	
	//Main_cam->Create_View_matrix(Vector(0, 50, -20), Vector(0, BG->Get_height(0, 0), 0), Vector(0, 1, 0));
	
	_box = new Shape_box;
	_box->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	_box->m_World_matrix.Set_Translation_matrix(0, 0, 0);
	

	return true;
}
bool Sample::Frame()
{
	// AnimSelector , Info default setting
	static bool	selectorOpen = false;
	static bool	infoOpen = false;

	static bool modelReady = false;
	

	// ImGui Frame()
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Main Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load"))
			{
				_fileDlg.Open();
			}
			if (ImGui::MenuItem("Reset"))
			{
				// reset model & reset action list
			}
			if (ImGui::MenuItem("Ingame Simulation"))
			{
				// Move key binding & Map loading & Set Camera
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Anim Selector")) 
			{
				if (selectorOpen != true) {
					selectorOpen = true;
				}
			}
	
			if (ImGui::MenuItem("Anim Info"))
			{
				if (infoOpen != true) {
					infoOpen = true;
				}
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	


	// File Dialogue

	_fileDlg.Display();

	if (_fileDlg.HasSelected())
	{
		_filePath = _fileDlg.GetSelected().string();
		_fileName =_fileDlg.GetSelected().filename().string();
		_fileDlg.ClearSelected();
		
		// Fbx Load
		FBX_loader* newFbx = new FBX_loader;
		if (newFbx->Init())
		{
			if (modelReady == false)
			{
				if (newFbx->Load(_filePath) > 0)															// mesh O
				{

					//m_fbx_table.insert(std::make_pair(to_mw(_fileName), _actionIdx++));
					m_fbx_list.push_back(newFbx);


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
					User_char->m_FBX_loader = newFbx;
					User_char->CreateConstantBuffer(m_pd3dDevice.Get());


					User_char->m_Anim_scene = User_char->m_FBX_loader->_animScene;
					Action_table action;
					action.Start_frame = User_char->m_Anim_scene.Start_frame;
					action.End_frame = User_char->m_Anim_scene.End_frame;
					action.Loop_state = true;
					User_char->m_Action_map.insert(std::make_pair(L"default", action));
					User_char->m_Current_action = User_char->m_Action_map.find(L"default")->second;

					modelReady = true;

					
				}
				else																					// mesh X
				{
					delete newFbx;

					// Print Error Message (LOAD MESH FIRST)

				}
			}
			else					// model ready
			{
				newFbx->Load(_filePath);
				newFbx->CreateConstantBuffer(m_pd3dDevice.Get());
				//m_fbx_table.insert(std::make_pair(to_mw(_fileName), _actionIdx++));
				m_fbx_list.push_back(newFbx);
				User_char->m_FBX_action_list.insert(std::make_pair(to_mw(_fileName), newFbx));
			}
		}
	}
	

	if (User_char == nullptr) return true;
	
	

	// Animation Selector 
	if(selectorOpen)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 350));
		if (ImGui::Begin("Anim Selector", &selectorOpen))
		{
			static int item_current_idx = 0;
			if (ImGui::Button("Play"))
			{
				User_char->m_FBX_action = m_fbx_list[item_current_idx];
				User_char->m_Anim_frame = 0;
				User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
				User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
				User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;

			}
			
			if (ImGui::BeginListBox("##anim",ImVec2(200,300)))
			{
				for (int n = 1; n < m_fbx_list.size(); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(m_fbx_list[n]->_fileName.c_str(), is_selected))
						item_current_idx = n;
				}
			
			
				ImGui::EndListBox();
			}
			

		}ImGui::End();
	}
	

	// Animation Info
	if (infoOpen)
	{
		ImGui::SetNextWindowSize(ImVec2(600, 150));
		if (ImGui::Begin(User_char->m_FBX_loader->_fileName.c_str(), &infoOpen))
		{
			static bool loop = true;
			if (User_char->m_FBX_action) {
				ImGui::Text("Current Animation : ");	ImGui::SameLine();
				ImGui::Text(User_char->m_FBX_action->_fileName.c_str());						// 현재 애니메이션
			}
			ImGui::Text("Current Frame : %f", User_char->m_Anim_frame);							// 현재 프레임
			ImGui::Text("Start : %d", User_char->m_Current_action.Start_frame);					// 시작 프레임
			ImGui::SameLine();
			ImGui::Text("End : %d", User_char->m_Current_action.End_frame);						// 끝 프레임
			ImGui::Text("Character Position : X -> %f , Y -> %f , Z -> %f", User_char->m_World_matrix._41, User_char->m_World_matrix._42, User_char->m_World_matrix._43);						// 캐릭터 위치
			
			if (ImGui::Button("Play"))
			{
				if (User_char->m_FBX_action)
				{
					User_char->m_Anim_scene.Frame_speed = 30.0f;
				}

			}
			ImGui::SameLine();
			if (ImGui::Button("Pause"))
			{
				if (User_char->m_FBX_action)
				{
					User_char->m_Anim_scene.Frame_speed = 0.0f;
				}

			}
			ImGui::SameLine();
			if (ImGui::Button("Replay"))
			{
				if (User_char->m_FBX_action)
				{
					User_char->m_Anim_frame = 0;
					User_char->m_Anim_scene.Frame_speed = 30.0f;
					User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
					User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
					User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
				}

			}
			ImGui::SameLine();
			ImGui::Checkbox("Loop", &loop);														// 루프 버튼
			User_char->m_Current_action.Loop_state = loop;

			// 프레임 슬라이더
			if (ImGui::DragFloat("##currentFrame", &User_char->m_Anim_frame, 0.1f, User_char->m_Current_action.Start_frame, User_char->m_Current_action.End_frame))
			{
				if (User_char->m_FBX_action)
				{
					User_char->m_Anim_scene.Frame_speed = 0.0f;
				}
			}ImGui::SameLine();
			ImGui::Text("Frame");	ImGui::SameLine();
			ImGui::InputFloat("Frame##inputfloat", &User_char->m_Anim_frame);


		}ImGui::End();
	}
	
	// Movement input -> change anim

	if (Input::GetInstance().GetKey('W') == KEY_HOLD)
	{
		User_char->m_FBX_action = m_fbx_table.find('W')->second;
		User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
		User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
	}
	else if (Input::GetInstance().GetKey('A') == KEY_HOLD)
	{
		User_char->m_FBX_action = m_fbx_table.find('A')->second;
		User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
		User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
	}
	else if (Input::GetInstance().GetKey('S') == KEY_HOLD)
	{
		User_char->m_FBX_action = m_fbx_table.find('S')->second;
		User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
		User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
	}
	else if (Input::GetInstance().GetKey('D') == KEY_HOLD)
	{
		User_char->m_FBX_action = m_fbx_table.find('D')->second;
		User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
		User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;
	}
	else 
	{
		User_char->m_FBX_action = m_fbx_table.find('0')->second;
		User_char->m_Anim_scene = User_char->m_FBX_action->_animScene;
		User_char->m_Current_action.Start_frame = User_char->m_FBX_action->_animScene.Start_frame;
		User_char->m_Current_action.End_frame = User_char->m_FBX_action->_animScene.End_frame;

		//User_char->m_Anim_frame = 0;
		//User_char->m_Current_action = User_char->m_Action_map.find(L"default")->second;
	}





	ClearD3D11DeviceContext(m_pImmediateContext.Get());
	Main_cam->Frame();

	Main_cam->m_Cam_pos.y = BG->Get_height(Main_cam->m_Cam_pos.x, Main_cam->m_Cam_pos.z - 50) + 100;
	Main_cam->Create_View_matrix(Main_cam->m_Cam_pos, Vector(Main_cam->m_Cam_pos.x, BG->Get_height(Main_cam->m_Cam_pos.x, Main_cam->m_Cam_pos.z - 50), Main_cam->m_Cam_pos.z - 50), Vector(0, 1, 0));
	Main_cam->Update_cam();

	User_char->Update_anim(m_pImmediateContext.Get());




	return true;
}
bool Sample::Render()
{

	if (User_char) 
	{
		
		User_char->m_World_matrix.Set_Scale_matrix(0.25f, 0.25f, 0.25f);


		User_char->m_World_matrix._41 = Main_cam->m_Cam_pos.x;
		User_char->m_World_matrix._43 = Main_cam->m_Cam_pos.z - 50;

		User_char->m_World_matrix._42 = BG->Get_height(User_char->m_World_matrix._41, User_char->m_World_matrix._43);
		
		

		//User_char->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
		
		

		User_char->SetMatrix(&User_char->m_World_matrix, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
		User_char->Render(m_pImmediateContext.Get());
	}

	if (User_char)
	{
		_box->m_World_matrix.Set_Translation_matrix(User_char->m_World_matrix._41, User_char->m_World_matrix._42, User_char->m_World_matrix._43);
		_box->SetMatrix(&_box->m_World_matrix, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
		_box->Render();
	}
	

	if (BG)	
	{
		BG->SetMatrix(nullptr, &Main_cam->m_View_matrix, &Main_cam->m_Proj_matrix);
		BG->Render();
	}
	

	return true;
}
bool Sample::Release()
{

	for (auto fbx : m_fbx_list)
	{
		fbx->Release();
	}

	if (Main_cam) 
	{
		Main_cam->Release();
		delete Main_cam;
	}

	if (User_char)
	{
		User_char->Release();
		delete User_char;
	}

	if (BG)
	{
		BG->Release();
		delete BG;
	}

	// release movement map
	for (auto iter = m_fbx_table.begin(); iter != m_fbx_table.end(); ++iter)
	{
		iter->second->Release();
	}
	m_fbx_table.clear();

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"Test", 800, 600);

	demo.Run();

	return 1;
}