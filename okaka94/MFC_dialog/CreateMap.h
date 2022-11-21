#pragma once


// CreateMap 대화 상자

class CreateMap : public CDialogEx
{
	DECLARE_DYNAMIC(CreateMap)

public:
	CreateMap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CreateMap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEMAP};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	UINT COMPONENT;
	CString Component;
	CString Length;
	CString Section;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedApply();
	CString Map_Width;
	CString Map_Height;
};
