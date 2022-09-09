#include "Timer.h"

float g_fGameTimer = 0.0f;
float g_fSecPerFrame = 0.0f;

bool Timer::Init() {
	m_fGameTimer = 0.0f;
	m_fElapseTimer = 10.0f;
	m_dwBeforeTime = timeGetTime();   // 1000 : 1sec
	return true;
}

bool Timer::Frame() {
	DWORD dwCurrentTime = timeGetTime();
	DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
	m_fElapseTimer = dwElapseTime / 1000.0f;			// 초 단위화
	m_fGameTimer += m_fElapseTimer;						// 플탐 누적(초)
	m_iFPSCounter++;									// 1프레임 증가
	m_fFPSTimer += m_fElapseTimer;						// 초당 프레임 계산을 위한 타이머
	
	if (m_fFPSTimer >= 1.0f) {							// 1초 지남
		m_iFPS =  m_iFPSCounter;						// 1초동안 실행한 프레임 수
		m_iFPSCounter = 0;								// 프레임 카운터 초기화
		m_fFPSTimer = m_fFPSTimer - 1.0f;				// 0으로 초기화하지 않고 1초만 뺌
	}

	g_fGameTimer = m_fGameTimer;						// 누적 플탐 전역변수로 저장
	g_fSecPerFrame = m_fElapseTimer;					// 프레임당 시간(초)
	m_dwBeforeTime = dwCurrentTime;						// 현재 프레임 진입시간 대입 (다음 프레임에서 현재 프레임 시간과 비교위함)
	
	return true;
}

bool Timer::Render() {

	m_szTimer = std::to_wstring(m_fGameTimer);			// 누적 플탐 스트링화
	m_szTimer += L"		";								// 자간
	m_szTimer += std::to_wstring(m_iFPS);				// FPS 스트링화
	m_szTimer += L"\n";
	OutputDebugString(m_szTimer.c_str());				// 디버깅화면에 출력

	return true;
}

bool Timer::Release() {

	return true;
}