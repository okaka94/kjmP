// CreateMap.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_dialog.h"
#include "CreateMap.h"
#include "afxdialogex.h"


// CreateMap 대화 상자

IMPLEMENT_DYNAMIC(CreateMap, CDialogEx)

CreateMap::CreateMap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, COMPONENT(0)
{

}

CreateMap::~CreateMap()
{
}

void CreateMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, COMPONENT);
}


BEGIN_MESSAGE_MAP(CreateMap, CDialogEx)
END_MESSAGE_MAP()


// CreateMap 메시지 처리기
