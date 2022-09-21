#include "Note.h"

//bool Note::Init() {
//
//	// 노트가 생성된 자리에서 시간 값 = 0;
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

	// 가이드라인 draw , 점점 감소
	// 충돌 판정 or 시간 초과되면 Release
	// 충돌 판정은 시간 값 리턴해주고 해당 시간에 맞춰서 노트 매니저에서 판정 이미지 생성 후 자동 소멸

}
	
	

//bool Note::Render() {
//
//	return true;
//}
//bool Note::Release() {
//
//	return true;
//}
