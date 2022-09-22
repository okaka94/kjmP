#include "Effect.h"

bool Effect::Frame() {

	timer += g_fSecPerFrame;

	if (timer >= 0.7f) {
		state = false;
	}

	return true;

	// 가이드라인 draw , 점점 감소
	// 충돌 판정 or 시간 초과되면 Release
	// 충돌 판정은 시간 값 리턴해주고 해당 시간에 맞춰서 노트 매니저에서 판정 이미지 생성 후 자동 소멸

}
