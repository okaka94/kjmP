#include "Sample.h"

bool Sample::Init()
{

	Cam_main = new Camera;
	Cam_main->Create_View_matrix(Vector(0, 10, -50), Vector(0, 0, 0), Vector(0, 1, 0));
	Cam_main->Create_Proj_matrix(1.0f, 100.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);


	Box_A = new Shape_box;
	Box_A->Create(m_pd3dDevice, m_pImmediateContext, L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	Box_A->m_World_matrix.Translation(0, 0, 2);
	
	/*ID3D11ShaderResourceView* SRV = MaskTex->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);*/



	return true;
}
bool Sample::Frame()
{
	Cam_main->Frame();
	Box_A->Frame();

	return true;
}
bool Sample::Render()
{


	if (Input::GetInstance().GetKey('V') == KEY_HOLD)
	{
		m_pImmediateContext->RSSetState(DXState::g_pDefaultRSWireFrame);
	}

	Box_A->SetMatrix(nullptr, &Cam_main->m_View_matrix, &Cam_main->m_Proj_matrix);
	Box_A->Render();
	
	return true;
}
bool Sample::Release()
{
	Box_A->Release();
	delete Box_A;

	Cam_main->Release();
	delete Cam_main;
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"LibraryTest",800,600);


	demo.Run();

	return 1;
}