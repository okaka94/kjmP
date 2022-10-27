#include "Sample.h"

bool Sample::Init()
{

	BG = new Map;
	// 2^n + 1로 빌드해야 공간 분할시 셀이 쪼개지지 않음
	BG->Build(512 + 1, 512 + 1);
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/NormalMap/stone_wall.bmp");


	Vector Cam_pos;

	// Top View
	Cam_pos = { 0.0f,10.0f,-1.0f };
	Cam[0].Create_View_matrix(Cam_pos, Vector(0, 0, 0), Vector(0, 1, 0));
	Cam[0].Create_Proj_matrix(1.0f, 100.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	// Front View
	Cam_pos = { 0.0f,0.0f,-10.0f };
	Cam[1].Create_View_matrix(Cam_pos, Vector(0, 0, 0), Vector(0, 1, 0));
	Cam[1].Create_Proj_matrix(1.0f, 100.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	// Side View
	Cam_pos = { 10.0f,0.0f,0.0f };
	Cam[2].Create_View_matrix(Cam_pos, Vector(0, 0, 0), Vector(0, 1, 0));
	Cam[2].Create_Proj_matrix(1.0f, 100.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	// User View
	Cam_pos = { 10.0f,10.0f,-10.0f };
	Cam[3].Create_View_matrix(Cam_pos, Vector(0, 0, 0), Vector(0, 1, 0));
	Cam[3].Create_Proj_matrix(1.0f, 100.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);



	Box_A = new Shape_box;
	Box_A->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	Box_A->m_World_matrix.Set_Translation_matrix(0, 0, 0);
	// axis
	Box_A->Set_axis();

	
	Vector vMax = Vector(-10000.0f, -10000.0f, -10000.0f);
	Vector vMin = Vector(10000.0f, 10000.0f, 10000.0f);
	for (int iVer = 0; iVer < 8; iVer++)															// 박스 구성은 첫 정점 8개로 확인 가능
	{
		if (Box_A->m_VertexList[iVer].p.x > vMax.x) vMax.x = Box_A->m_VertexList[iVer].p.x;
		if (Box_A->m_VertexList[iVer].p.y > vMax.y) vMax.y = Box_A->m_VertexList[iVer].p.y;
		if (Box_A->m_VertexList[iVer].p.z > vMax.z) vMax.z = Box_A->m_VertexList[iVer].p.z;
	
		if (Box_A->m_VertexList[iVer].p.x < vMin.x) vMin.x = Box_A->m_VertexList[iVer].p.x;
		if (Box_A->m_VertexList[iVer].p.y < vMin.y) vMin.y = Box_A->m_VertexList[iVer].p.y;
		if (Box_A->m_VertexList[iVer].p.z < vMin.z) vMin.z = Box_A->m_VertexList[iVer].p.z;			// Max, Min 벡터 구축
	}
	// 화면에 가득채우게 만드는 함수
	Cam[0].Set_Obj_View_matrix(vMax, vMin, Cam[0].m_FOV_Y);
	Cam[1].Set_Obj_View_matrix(vMax, vMin, Cam[1].m_FOV_Y);
	Cam[2].Set_Obj_View_matrix(vMax, vMin, Cam[2].m_FOV_Y);
	Cam[3].Set_Obj_View_matrix(vMax, vMin, Cam[3].m_FOV_Y);


	return true;
}
bool Sample::Frame()
{
	////--------------------------------------------------------------------------------------
	//// 오브젝트 월드 행렬 컨트롤 
	////--------------------------------------------------------------------------------------
	//if (Input::GetInstance().GetKey(VK_LEFT) == KEY_HOLD)
	//{
	//	m_fYaw += g_fSecPerFrame;
	//}
	//if (Input::GetInstance().GetKey(VK_RIGHT) == KEY_HOLD)
	//{
	//	m_fYaw -= g_fSecPerFrame;
	//}
	//if (Input::GetInstance().GetKey(VK_UP) == KEY_HOLD)
	//{
	//	m_fPitch += g_fSecPerFrame;
	//}
	//if (Input::GetInstance().GetKey(VK_DOWN) == KEY_HOLD)
	//{
	//	m_fPitch -= g_fSecPerFrame;
	//}
	//if (Input::GetInstance().GetKey(VK_HOME) == KEY_HOLD)
	//{
	//	m_fRoll += g_fSecPerFrame;
	//}
	//if (Input::GetInstance().GetKey(VK_END) == KEY_HOLD)
	//{
	//	m_fRoll -= g_fSecPerFrame;
	//}


	//Matrix rot_mat;
	//rot_mat = rot_mat.Make_YPR_matrix(m_fYaw, m_fPitch, m_fRoll);
	//Box_A->m_World_matrix = Box_A->m_World_matrix * rot_mat;


	

	


	//m_world_mat.Set_YPR_matrix(m_fYaw, m_fPitch, m_fRoll);

	Quaternion Q = { 3,2,5, PI * 0.25f };

	m_world_mat = Q.RotationQ_to_Mat();


	return true;
}
bool Sample::Render()
{


	if (Input::GetInstance().GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(DXState::g_pDefaultRSWireFrame);
	}

	D3D11_VIEWPORT vp;

	// top V
	vp.Width = g_rtClient.right/2;
	vp.Height = g_rtClient.bottom/2;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	Box_A->SetMatrix(&m_world_mat, &Cam[0].m_View_matrix, &Cam[0].m_Proj_matrix);
	Box_A->Render();

	BG->SetMatrix(nullptr, &Cam[0].m_View_matrix, &Cam[0].m_Proj_matrix);
	BG->Render();
	

	// front V
	vp.Width = g_rtClient.right / 2;
	vp.Height = g_rtClient.bottom / 2;
	vp.TopLeftX = g_rtClient.right / 2;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	Box_A->SetMatrix(&m_world_mat, &Cam[1].m_View_matrix, &Cam[1].m_Proj_matrix);
	Box_A->Render();

	BG->SetMatrix(nullptr, &Cam[1].m_View_matrix, &Cam[1].m_Proj_matrix);
	BG->Render();						

	// side V
	vp.Width = g_rtClient.right / 2;
	vp.Height = g_rtClient.bottom / 2;
	vp.TopLeftX = 0;
	vp.TopLeftY = g_rtClient.bottom / 2;;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	Box_A->SetMatrix(&m_world_mat, &Cam[2].m_View_matrix, &Cam[2].m_Proj_matrix);
	Box_A->Render();

	BG->SetMatrix(nullptr, &Cam[2].m_View_matrix, &Cam[2].m_Proj_matrix);
	BG->Render();
	
	// side V
	vp.Width = g_rtClient.right / 2;
	vp.Height = g_rtClient.bottom / 2;
	vp.TopLeftX = g_rtClient.right / 2;
	vp.TopLeftY = g_rtClient.bottom / 2;;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	Box_A->SetMatrix(&m_world_mat, &Cam[3].m_View_matrix, &Cam[3].m_Proj_matrix);
	Box_A->Render();

	BG->SetMatrix(nullptr, &Cam[3].m_View_matrix, &Cam[3].m_Proj_matrix);
	BG->Render();
	
	return true;
}
bool Sample::Release()
{
	Box_A->Release();
	delete Box_A;
		
	//Cam_main->Release();
	//delete Cam_main;
	
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