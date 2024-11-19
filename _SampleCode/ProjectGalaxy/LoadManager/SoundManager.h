#pragma once
#include<map>
#include<string>
#include"DxLib.h"
struct SoundInfo {
	int handle;//�n���h��
	bool used;//��x�ȏ�g�p�ς݂��H
};
class SoundManager
{
private:
	std::map<std::string, SoundInfo> m_pathAndSoundInfoes;
	int m_soundVol;

public:
	SoundManager();
	~SoundManager();

	int GetSoundVol() const { return m_soundVol; }

	static SoundManager& GetInstance();
	void ChangeSoundVolume(int vol);
	int GetSoundData(const char* filepath);

};

