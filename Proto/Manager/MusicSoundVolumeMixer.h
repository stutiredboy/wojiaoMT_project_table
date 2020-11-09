//////////////////////////////////////////////////////////////////////////
// File:		MusicSoundVolumeMixer.h
// Author:	���
// Date:		2016/04/21
//////////////////////////////////////////////////////////////////////////

#ifndef _MusicSoundVolumeMixer_h_
#define _MusicSoundVolumeMixer_h_

#include "Singleton.hpp"
#include <set>

#include <string>

// ���ֺ���Ч���������������������Чʱ�����ֵ������ʵ����ͣ���Ч������Ϻ��ٻָ����ֵ�������

class MusicSoundVolumeMixer : public CSingleton < MusicSoundVolumeMixer >
{
private:
	const float MAX_FADE_TIME = 0.5f;  // ���ֵ���������/������ʱ��
	const float VOLUME_LOW_PERCENT = 0.3f;  // �����������������İٷ�֮����

	enum STATE
	{
		STATE_VOLUME_NORMAL,
		STATE_VOLUME_DOWN,
		STATE_VOLUME_LOW,
		STATE_VOLUME_UP,
	};

	typedef std::set<std::string> StringSet;

private:
	STATE mState;
	StringSet mSounds;
	float mVolume;
	float mFadingTime;
	float mVolumeFactor;

public:
	MusicSoundVolumeMixer();

	void update(int dtMs);

	// �������ֵ�����
	void setBackgroundMusicVolume(float val);

	// ֪ͨ����Ч��ʼ������
	void notifySoundStart(const std::string& pszFilePath);
	// ֪ͨ��Ч���������
	void notifySoundEnd(const std::string& pszFilePath);

private:
	void updateVolumeDown(float dt);
	void updateVolumeUp(float dt);
	void checkSoundIsPlaying();
};

#endif