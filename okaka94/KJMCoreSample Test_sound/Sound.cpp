#include "Sound.h"

bool Sound::Load(std::string filename) {
	FMOD_RESULT fr = m_pSystem->createSound(filename.c_str(), FMOD_DEFAULT, nullptr, &m_pSound);
	if (fr == FMOD_OK) {
		//fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	}

	return true;
}

bool Sound::Is_play() {
	bool state_playing = false;						// ä���� ������쵵 false
	if (m_pChannel != nullptr) {
		m_pChannel->isPlaying(&state_playing);
	}
	return state_playing;
}

bool Sound::Play(bool state_loop) {

	if (Is_play() == false) {						// ���� ����� X -> ����ϱ�
		FMOD_RESULT fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (fr == FMOD_OK) {
			Switch_loop(state_loop);
		}
	}
	return true;
}

void Sound::Pause_Play() {
	if (m_pChannel == nullptr) return;
	bool state_pause;
	m_pChannel->getPaused(&state_pause);
	m_pChannel->setPaused(!state_pause);
}

void Sound::Up_volume(float volume) {
	if (m_pChannel == nullptr) return;
	m_fVolume += volume;
	m_fVolume = min(1.0f, m_fVolume);		// �ִ밪�� 1 ���� �ʵ���
	m_pChannel->setVolume(m_fVolume);
}


void Sound::Down_volume(float volume) {
	if (m_pChannel == nullptr) return;
	m_fVolume -= volume;
	m_fVolume = max(0.0f, m_fVolume);		// �ּҰ��� 0 �Ʒ��� ���� �ʵ���
	m_pChannel->setVolume(m_fVolume);
}

void Sound::Switch_loop(bool state_loop) {
	if (state_loop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);
	
}

bool Sound::Init() {
	
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

bool Sound::Frame() {

	return true;
}

bool Sound::Render() {

	return true;
}

bool Sound::Release() {

	if (m_pSound) m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
	// channel�� ���� ���� ���ص� ��
	return true;
}