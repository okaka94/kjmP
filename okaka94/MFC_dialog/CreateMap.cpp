// CreateMap.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_dialog.h"
#include "CreateMap.h"
#include "afxdialogex.h"


// CreateMap 대화 상자

IMPLEMENT_DYNAMIC(CreateMap, CDialogEx)

CreateMap::CreateMap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CREATEMAP, pParent)
	//, COMPONENT(0)
	//, Component(_T(""))
	//, Length(_T(""))
	//, Section(_T(""))
	, Component(_T("컴포넌트"))
	, Length(_T("길이"))
	, Section(_T("섹션"))
	, Map_Width(_T(""))
	, Map_Height(_T(""))
{

}

CreateMap::~CreateMap()
{
}

void CreateMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT3, COMPONENT);
	DDX_Text(pDX, IDC_Component, Component);
	DDX_Text(pDX, IDC_Length, Length);
	DDX_Text(pDX, IDC_Section, Section);
	DDX_Text(pDX, IDC_WIDTH, Map_Width);
	DDX_Text(pDX, IDC_HEIGHT, Map_Height);
}


BEGIN_MESSAGE_MAP(CreateMap, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateMap::OnBnClickedOk)
	ON_BN_CLICKED(IDC_APPLY, &CreateMap::OnBnClickedApply)
END_MESSAGE_MAP()


// CreateMap 메시지 처리기


void CreateMap::OnBnClickedOk()
{

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


BOOL CreateMap::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//Component = "컴포넌트 수";
	//Section = "섹션 수";
	//Length = "길이";

	UpdateData(FALSE);


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CreateMap::OnBnClickedApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);

	theApp.m_Sample.BG->m_Height_list.clear();
	theApp.m_Sample.BG->Release();
	theApp.m_Sample.BG->Build(theApp.m_Sample.m_pd3dDevice.Get(), _ttoi(Map_Width), _ttoi(Map_Height), theApp.m_Sample.Main_cam);
	theApp.m_Sample.BG->Create(theApp.m_Sample.m_pd3dDevice.Get(), theApp.m_Sample.m_pImmediateContext.Get(), L"DefaultShape_PNCT.txt", L"../../data/NormalMap/stone_wall.bmp");
	theApp.m_Sample.BG->Create_Qtree(theApp.m_Sample.m_pd3dDevice.Get(), theApp.m_Sample.Main_cam);
}
