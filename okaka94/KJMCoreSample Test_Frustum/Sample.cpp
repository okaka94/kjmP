#include "Sample.h"

bool Sample::Init()
{
		
	BG = new Map;
	// 2^n + 1로 빌드해야 공간 분할시 셀이 쪼개지지 않음
	BG->Build(512 + 1, 512 + 1);
	BG->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/NormalMap/stone_wall.bmp");

	Box_A = new Shape_box;
	Box_A->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	Box_A->m_World_matrix.Set_Translation_matrix(0, 0, 0);
	// axis
	Box_A->Set_axis();

	
		
	Main_cam.Create_View_matrix(Vector(0,10,-30), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam.Create_Proj_matrix(1.0f, 150.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	for (int iBox = 0; iBox < 100; iBox++)
	{
		m_vBoxPosition[iBox] = Vector(25 - rand() % 50, 0.0f, 25 - rand() % 50);

	}

	return true;
}
bool Sample::Frame()
{
		
	/*static float angle = 0.0f;
	if (Input::GetInstance().GetKey(VK_UP) == KEY_HOLD)
	{
		angle += g_fSecPerFrame*10.0f;
	}
	if (Input::GetInstance().GetKey(VK_DOWN) == KEY_HOLD)
	{
		angle -= g_fSecPerFrame*10.0f;
	}

	Quaternion Q = { 1,1,0,angle };

	m_world_mat = Q.RotationQ_to_Mat();*/

	Main_cam.Frame();


	return true;
}
bool Sample::Render()
{


	if (Input::GetInstance().GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(DXState::g_pDefaultRSWireFrame);
	}

	

	//Box_A->SetMatrix(&m_world_mat, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
	//P_POSITION ret = Main_cam.m_Frustum.Classify_point({ 0,0,0 });
	//if (ret)
	//{
	//	Box_A->Render();
	//}

	/////  box render /////
	for (int iBox = 0; iBox < 100; iBox++)
	{
		m_world_mat._41 = m_vBoxPosition[iBox].x;
		m_world_mat._42 = m_vBoxPosition[iBox].y;
		m_world_mat._43 = m_vBoxPosition[iBox].z;
						

		Box_A->SetMatrix(&m_world_mat, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
		P_POSITION ret = Main_cam.m_Frustum.Classify_point(m_vBoxPosition[iBox]);
		if (ret)
		{
			Box_A->Render();
		}

	}

	BG->SetMatrix(nullptr, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
	//BG->Render();
	
	return true;
}
bool Sample::Release()
{
	Box_A->Release();
	delete Box_A;

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