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
	m_fElapseTimer = dwElapseTime / 1000.0f;			// �� ����ȭ
	m_fGameTimer += m_fElapseTimer;						// ��Ž ����(��)
	m_iFPSCounter++;									// 1������ ����
	m_fFPSTimer += m_fElapseTimer;						// �ʴ� ������ ����� ���� Ÿ�̸�
	
	if (m_fFPSTimer >= 1.0f) {							// 1�� ����
		m_iFPS =  m_iFPSCounter;						// 1�ʵ��� ������ ������ ��
		m_iFPSCounter = 0;								// ������ ī���� �ʱ�ȭ
		m_fFPSTimer = m_fFPSTimer - 1.0f;				// 0���� �ʱ�ȭ���� �ʰ� 1�ʸ� ��
	}

	g_fGameTimer = m_fGameTimer;						// ���� ��Ž ���������� ����
	g_fSecPerFrame = m_fElapseTimer;					// �����Ӵ� �ð�(��)
	m_dwBeforeTime = dwCurrentTime;						// ���� ������ ���Խð� ���� (���� �����ӿ��� ���� ������ �ð��� ������)
	
	return true;
}

bool Timer::Render() {

	m_szTimer = std::to_wstring(m_fGameTimer);			// ���� ��Ž ��Ʈ��ȭ
	m_szTimer += L"		";								// �ڰ�
	m_szTimer += std::to_wstring(m_iFPS);				// FPS ��Ʈ��ȭ
	m_szTimer += L"\n";
	OutputDebugString(m_szTimer.c_str());				// �����ȭ�鿡 ���

	return true;
}

bool Timer::Release() {

	return true;
}