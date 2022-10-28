#include "Sample.h"

bool Sample::Init()
{
		
	Box_A = new Shape_box;
	Box_A->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	Box_A->m_World_matrix.Set_Translation_matrix(0, 5, 0);
	// axis
	Box_A->Set_axis();

	
	////////////////////////// Model_View Cam /////////////////////

	
	Main_cam.Create_View_matrix(Vector(0,1,-15), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam.Create_Proj_matrix(1.0f, 1000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);



	return true;
}
bool Sample::Frame()
{
		
	static float angle = 0.0f;
	if (Input::GetInstance().GetKey(VK_UP) == KEY_HOLD)
	{
		angle += g_fSecPerFrame*10.0f;
	}
	if (Input::GetInstance().GetKey(VK_DOWN) == KEY_HOLD)
	{
		angle -= g_fSecPerFrame*10.0f;
	}

	Quaternion Q = { 1,1,0,angle };

	m_world_mat = Q.RotationQ_to_Mat();

	Main_cam.Frame();


	return true;
}
bool Sample::Render()
{


	if (Input::GetInstance().GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(DXState::g_pDefaultRSWireFrame);
	}

	

	Box_A->SetMatrix(&m_world_mat, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
	Box_A->Render();

	
	return true;
}
bool Sample::Release()
{
	Box_A->Release();
	delete Box_A;
		

	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}