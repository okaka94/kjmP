#include "Sample.h"

bool Sample::Init()
{
		
	Main_cam.Create_View_matrix(Vector(0, 50, -30), Vector(0, 0, 0), Vector(0, 1, 0));
	Main_cam.Create_Proj_matrix(1.0f, 10000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	Main_cam.m_Frustum.Create_frustum_box(m_pd3dDevice.Get(), m_pImmediateContext.Get());

	BG = new Map;
	// 2^n + 1로 빌드해야 공간 분할시 셀이 쪼개지지 않음
	BG->Build(m_pd3dDevice.Get(), 512 + 1, 512 + 1,&Main_cam);
	BG->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShape_PNCT.txt", L"../../data/NormalMap/stone_wall.bmp");
	BG->Create_Qtree(m_pd3dDevice.Get(), &Main_cam);

	Box_A = new Shape_box;
	Box_A->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"DefaultShape_Constant.txt", L"../../data/object/cncr25S.bmp");
	Box_A->m_World_matrix.Set_Translation_matrix(0, 0, 0);
	//MM_cam.Create_View_matrix(Vector(0, 70, 0.0), Vector(0, 0, 1), Vector(0, 1, 0));
	//MM_cam.Create_Proj_matrix(1.0f, 1000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);

	for (int iBox = 0; iBox < 100; iBox++)
	{
		//m_vBoxPosition[iBox] = Vector(25 - rand() % 50, 0.0f, 25 - rand() % 50);

	}
		



	return true;
}
bool Sample::Frame()
{
		
	Main_cam.Frame();

	return true;
}
bool Sample::Render()
{
	
	for (int iBox = 0; iBox < 100; iBox++)
	{
		m_world_mat._41 = m_vBoxPosition[iBox].x;
		m_world_mat._42 = m_vBoxPosition[iBox].y;
		m_world_mat._43 = m_vBoxPosition[iBox].z;

		Vector center = m_vBoxPosition[iBox];

		OBB Box;
		Box.set_AABB(center, 1, 1, sqrt(3));

		//SphereObj.v_center = m_vBoxPosition[iBox];
		//SphereObj.r = sqrt(3.0f);


		Box_A->SetMatrix(&m_world_mat, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
		P_POSITION ret = Main_cam.m_Frustum.Classify_OBB(Box);
		if (ret)
		{
			Box_A->m_cbData.g_Color = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
			//Box_A->m_cbData.g_Color = Vector4D(1.0f, 0.0f, 0.0f, 1.0f);
			Box_A->UpdateConstantBuffer();
			Box_A->Render();
		}

	}
	W_STR text = mtw("Number of rendered nodes: ") + std::to_wstring(BG->Map_Qtree.m_Draw_list.size());
	Writer::GetInstance().Draw(5, 90, text, { 1,0,1,1 });

	BG->SetMatrix(nullptr, &Main_cam.m_View_matrix, &Main_cam.m_Proj_matrix);
	BG->Render();
	
	
	
	
	
	
	//// mini map
	//vp.Width = g_rtClient.right / 3;
	//vp.Height = g_rtClient.bottom / 3;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//vp.MinDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	//m_pImmediateContext->RSSetViewports(1, &vp);										// 기존 뷰포트

	//

	//for (int iBox = 0; iBox < 100; iBox++)
	//{
	//	m_world_mat._41 = m_vBoxPosition[iBox].x;
	//	m_world_mat._42 = m_vBoxPosition[iBox].y;
	//	m_world_mat._43 = m_vBoxPosition[iBox].z;

	//	Vector center = m_vBoxPosition[iBox];

	//	OBB Box;
	//	Box.set_AABB(center, 1, 1, sqrt(3));


	//	Box_A->SetMatrix(&m_world_mat, &MM_cam.m_View_matrix, &MM_cam.m_Proj_matrix);
	//	P_POSITION ret = Main_cam.m_Frustum.Classify_OBB(Box);
	//	//SphereObj.v_center = m_vBoxPosition[iBox];
	//	//SphereObj.r = sqrt(3.0f);

	//	//P_POSITION ret = Main_cam.m_Frustum.Classify_point(center);
	//	//P_POSITION ret = Main_cam.m_Frustum.Classify_sphere(SphereObj);
	//	if (ret)
	//	{
	//		Box_A->m_cbData.g_Color = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
	//	}
	//	else
	//	{
	//		Box_A->m_cbData.g_Color = Vector4D(1.0f, 0.0f, 0.0f, 1.0f);
	//	}
	//		Box_A->UpdateConstantBuffer();
	//		Box_A->Render();
	//	
	//		
	//}


	//Main_cam.m_Frustum.Render(&MM_cam.m_View_matrix, &MM_cam.m_Proj_matrix);
	

	return true;
}
bool Sample::Release()
{
	

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