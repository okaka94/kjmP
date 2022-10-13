#include "Effect.h"

bool Effect::Frame() {

	timer += g_fSecPerFrame;

	if (timer >= 0.3f) {
		state = false;
	}
	m_fOpacity -= g_fSecPerFrame*2  ;
	m_fOpacity = max(m_fOpacity, 0);

	m_VertexList[0].c = { 1,1,1,m_fOpacity };
	m_VertexList[1].c = { 1,1,1,m_fOpacity };
	m_VertexList[2].c = { 1,1,1,m_fOpacity };
	m_VertexList[3].c = { 1,1,1,m_fOpacity };
	UpdateVertexBuffer();
	return true;

	// ���̵���� draw , ���� ����
	// �浹 ���� or �ð� �ʰ��Ǹ� Release
	// �浹 ������ �ð� �� �������ְ� �ش� �ð��� ���缭 ��Ʈ �Ŵ������� ���� �̹��� ���� �� �ڵ� �Ҹ�

}
