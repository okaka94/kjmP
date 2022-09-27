#include "Sound.h"
#include <tchar.h>

bool Sound::Load(FMOD::System* pSystem, std::wstring filename) {
	m_pSystem = pSystem;
	FMOD_RESULT fr = m_pSystem->createSound(to_wm(filename).c_str(), FMOD_DEFAULT, nullptr, &m_pSound);
	if (fr == FMOD_OK) {
		m_pSound->getLength(&m_Total_time, FMOD_TIMEUNIT_MS);
	}

	return true;
}

bool Sound::Is_play() {
	bool state_playing = false;						// 채널이 없을경우도 false
	if (m_pChannel != nullptr) {
		m_pChannel->isPlaying(&state_playing);
	}
	return state_playing;
}

bool Sound::Play(bool state_loop) {

	if (Is_play() == false) {						// 현재 재생중 X -> 재생하기
		FMOD_RESULT fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (fr == FMOD_OK) {
			Switch_loop(state_loop);
		}
	}
	return true;
}

bool Sound::Play_effect(bool state_loop) {

	FMOD_RESULT fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (fr == FMOD_OK) {
			Switch_loop(state_loop);
		}
	
	return true;
}

void Sound::Stop() {
	m_pChannel->stop();
}

void Sound::Pause_Play() {
	if (m_pChannel == nullptr) return;
	bool state_pause;
	m_pChannel->getPaused(&state_pause);
	m_pChannel->setPaused(!state_pause);
}

void Sound::Set_volume(float volume) {
	if (m_pChannel == nullptr) return;
	m_pChannel->setVolume(volume);
}

void Sound::Up_volume(float volume) {
	if (m_pChannel == nullptr) return;
	m_fVolume += volume;
	m_fVolume = min(1.0f, m_fVolume);		// 최대값이 1 넘지 않도록
	m_pChannel->setVolume(m_fVolume);
}


void Sound::Down_volume(float volume) {
	if (m_pChannel == nullptr) return;
	m_fVolume -= volume;
	m_fVolume = max(0.0f, m_fVolume);		// 최소값이 0 아래로 가지 않도록
	m_pChannel->setVolume(m_fVolume);
}

void Sound::Switch_loop(bool state_loop) {
	if (state_loop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);
	
}

bool Sound::Init() {
	
	/*FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);*/
	return true;
}

bool Sound::Frame() {

	//m_pSystem->update();

	if (m_pChannel)
	{
		unsigned int ms = 0;
		m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
		TCHAR szBuffer[256] = { 0, };
		_stprintf_s(szBuffer, _T("현 시간 %02d:%02d:%02d, 총 시간 %02d:%02d:%02d \n"), ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 60, m_Total_time / 1000 / 60, m_Total_time / 1000 % 60 , m_Total_time / 10 % 60);
		OutputDebugString(szBuffer);
		//m_szBuffer = szBuffer;
	}
	return true;
}

bool Sound::Render() {

	return true;
}

bool Sound::Release() {

	if (m_pSound) m_pSound->release();
	/*m_pSystem->close();
	m_pSystem->release();*/
	// channel은 따로 해제 안해도 됨
	return true;
}