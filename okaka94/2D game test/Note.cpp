#include "Note.h"

//bool Note::Init() {
//
//	// ��Ʈ�� ������ �ڸ����� �ð� �� = 0;
//
//	return true;
//}
bool Note::Frame() {

	timer += g_fSecPerFrame;
		if (timer >= 0.95f && timer <= 1.1f) {
			score = 300;
		}
		else if (timer >= 0.5f && timer <= 1.2f) {
			score = 100;
		}
		else if (timer < 0.5f || (timer > 1.2f && timer <= 1.3f)) {
			score = 50;
		}
		else {
			score = 0;
			state = false;
		}
	return true;

	// ���̵���� draw , ���� ����
	// �浹 ���� or �ð� �ʰ��Ǹ� Release
	// �浹 ������ �ð� �� �������ְ� �ش� �ð��� ���缭 ��Ʈ �Ŵ������� ���� �̹��� ���� �� �ڵ� �Ҹ�

}
	
	

//bool Note::Render() {
//
//	return true;
//}
//bool Note::Release() {
//
//	return true;
//}
