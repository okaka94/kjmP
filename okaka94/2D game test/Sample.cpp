#include "Sample.h"
#include "Note_manager.h"



bool Sample::Init()
{
	
	Note_manager::GetInstance().SetDevice(m_pd3dDevice, m_pImmediateContext);
	Note_manager::GetInstance().Init();

	
	// map load
	Map = new Base_object;
	Map->Create(m_pd3dDevice, m_pImmediateContext, L"../../data/shader/DefaultShape.txt", L"../../data/EBA/background_low_ex.png");
	

	return true;
}
bool Sample::Frame()
{
	Map->Frame();

	static float timer = 0.0f;
	timer += g_fSecPerFrame;





	if (timer > 3.0f) {
		Note_manager::GetInstance().Create_note("B0");
		timer = 1.0f;
	}
	
	

	if(Input::GetInstance().GetKey(VK_LBUTTON) == KEY_PUSH) {
		float x = Input::GetInstance().m_ptPos.x;
		float y = Input::GetInstance().m_ptPos.y;
		Note_manager::GetInstance().Judge_note(x, y);

	}
	
		

		//Note_manager::GetInstance().Release_note(g_fGameTimer);
	//}
		
	



	
	return true;
}
bool Sample::Render()
{
	Map->Render();

	if(!Note_manager::GetInstance().Get_list().empty()){
		//Note_manager::GetInstance().Get_list().front()->Render();
		for (int i = 0; i < Note_manager::GetInstance().Get_list().size(); i++) {
			Note_manager::GetInstance().Get_list()[i]->Render();			
		}
	}
	
	// note frame level 
	m_writer.Draw_circle(130, 130, 100, { 1,1,1,1 });
	m_writer.Draw_circle(130, 130, 30, { 1,1,1,1 });


	ID3D11ShaderResourceView* SRV = Note_manager::GetInstance().Get_pMask()->Get_SRV();
	m_pImmediateContext->PSSetShaderResources(1, 1, &SRV);
	
	return true;
}
bool Sample::Release()
{
	Map->Release();
	Note_manager::GetInstance().Release();
	
	return true;
}


int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Sample demo;
	demo.SetWindow(hinstance, L"2D test",800,600);


	demo.Run();

	return 1;
}