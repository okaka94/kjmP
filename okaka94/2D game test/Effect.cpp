#include "Effect.h"

bool Effect::Frame() {

	timer += g_fSecPerFrame;

	if (timer >= 0.7f) {
		state = false;
	}

	return true;

	// ���̵���� draw , ���� ����
	// �浹 ���� or �ð� �ʰ��Ǹ� Release
	// �浹 ������ �ð� �� �������ְ� �ش� �ð��� ���缭 ��Ʈ �Ŵ������� ���� �̹��� ���� �� �ڵ� �Ҹ�

}
