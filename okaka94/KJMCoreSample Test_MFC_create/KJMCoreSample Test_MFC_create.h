
// KJMCoreSample Test_MFC_create.h: KJMCoreSample Test_MFC_create 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       
#include "Sample.h"			// Sample 헤더 추가


// CKJMCoreSampleTestMFCcreateApp:
// 이 클래스의 구현에 대해서는 KJMCoreSample Test_MFC_create.cpp을(를) 참조하세요.
//

class CKJMCoreSampleTestMFCcreateApp : public CWinAppEx
{
public:
	CKJMCoreSampleTestMFCcreateApp() noexcept;
	Sample		m_Sample;	// 멤버에 Sample 추가

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CKJMCoreSampleTestMFCcreateApp theApp;
