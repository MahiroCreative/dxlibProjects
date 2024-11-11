#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "SoundManager.h"

namespace
{
	constexpr int VOLUME_MAX = 255;
}

SoundManager::SoundManager() :
	m_bgmVolume(VOLUME_MAX),
	m_seVolume(VOLUME_MAX),
	m_nowPlayBgm(-1),
	m_soundHandle(-1),
	m_soundSavePos(0),
	m_isStop(false)
{
}

SoundManager::~SoundManager()
{
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager snd;
	return snd;
}

void SoundManager::Update()
{
	if (m_isStop) return;

	m_saveSeList.remove_if(
		[](const auto& info)
		{
			return !CheckSoundMem(info.handle);
		});
}

void SoundManager::StopNowPlaySe()
{
	m_isStop = true;

	for (auto& info : m_saveSeList)
	{
		info.savePos = GetSoundCurrentPosition(info.handle);
		StopSoundMem(info.handle);
	}
}

void SoundManager::RestartStopedSe()
{
	m_isStop = false;

	for (auto& info : m_saveSeList)
	{
		SetSoundCurrentTime(info.savePos, info.handle);
		ChangeNextPlayVolumeSoundMem(m_seVolume, info.handle);
		PlaySoundMem(info.handle, DX_PLAYTYPE_BACK, false);
	}
}

void SoundManager::PlayBgm(int soundHandle, bool isLoop, bool isSoundPosSave)
{
	if (soundHandle < 0)
	{
		soundHandle = m_nowPlayBgm;
	}

	if (IsNowPlay(soundHandle)) return;

	// 音量の変更
	ChangeNextPlayVolumeSoundMem(m_bgmVolume, soundHandle);

	if (isSoundPosSave)
	{
		SetSoundCurrentTime(m_soundSavePos, soundHandle);
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, isLoop);
	}
	else
	{
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, isLoop);
	}

	m_nowPlayBgm = soundHandle;
}

void SoundManager::PlayFadeBgm(int soundHandle, float rate, bool isLoop)
{
	if (soundHandle < 0)
	{
		soundHandle = m_nowPlayBgm;
	}

	if (IsNowPlay(soundHandle))
	{
		SetBgmVol(rate);
		return;
	}

	// 音量の変更
	ChangeNextPlayVolumeSoundMem(static_cast<int>(m_bgmVolume * rate), soundHandle);

	// ループがONの場合はBGMが終了次第先頭に戻る
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, isLoop);

	m_nowPlayBgm = soundHandle;
}

void SoundManager::PlaySe(int seHandle, bool isOption)
{
	// 音量の変更
	ChangeNextPlayVolumeSoundMem(m_seVolume, seHandle);

	auto err = PlaySoundMem(seHandle, DX_PLAYTYPE_BACK, true);
	assert(err != -1);
//	PlaySoundMem(seHandle, DX_PLAYTYPE_NORMAL, true);
	m_soundHandle = seHandle;

	if (!isOption)
	{
		m_saveSeList.emplace_back(SaveSeData{seHandle, 0});
	}
}

void SoundManager::PlayFadeSe(int handle, float rate, bool isOption)
{
	if (IsNowPlay(handle))
	{
		ChangePlaySeVol(handle, rate);
		return;
	}

	ChangeNextPlayVolumeSoundMem(static_cast<int>(m_seVolume * rate), handle);

	PlaySoundMem(handle, DX_PLAYTYPE_BACK, true);

	if (!isOption)
	{
		m_saveSeList.emplace_back(SaveSeData{ handle, 0 });
	}
}

void SoundManager::StopBGM(int soundHandle, bool isSoundPosSave)
{
	if (soundHandle < 0)
	{
		soundHandle = m_nowPlayBgm;
	}

	StopSoundMem(soundHandle);

	// 音声再生場所の保存
	if (isSoundPosSave)
	{
		m_soundSavePos = GetSoundCurrentPosition(soundHandle);
	}
}

void SoundManager::Stop(int handle)
{
	StopSoundMem(handle);
}

void SoundManager::ChangeBgmVol(int volume, bool isApp)
{
	m_bgmVolume = std::max<int>(std::min<int>(volume, VOLUME_MAX), 0);
	
	if (isApp)
	{
		SetBgmVol();
	}
}

void SoundManager::ChangeSeVol(int volume)
{
	m_seVolume = std::max<int>(std::min<int>(volume, VOLUME_MAX), 0);

	PlaySe(m_soundHandle);
}

int SoundManager::GetMaxVol() const
{
	return VOLUME_MAX;
}

bool SoundManager::IsNowPlay(int handle) const
{
	auto err = CheckSoundMem(handle);
	assert(err != -1);
	return err;
}

float SoundManager::GetBgmVolRate() const
{
	return static_cast<float>(m_bgmVolume) / static_cast<float>(VOLUME_MAX);
}

float SoundManager::GetSeVolRate() const
{
	return static_cast<float>(m_seVolume) / static_cast<float>(VOLUME_MAX);
}

void SoundManager::SetBgmVol(float rate)
{
	// 再生中でなければ終了
	if (!IsNowPlay(m_nowPlayBgm)) return;

	// ズレていたらより正確なこっちで GetSoundCurrentTime 
	LONGLONG soundPosition = GetSoundCurrentPosition(m_nowPlayBgm);

	// 一度サウンドを止める
	StopSoundMem(m_nowPlayBgm);

	// 再生位置を設定
	SetSoundCurrentTime(soundPosition, m_nowPlayBgm);

	// 音量の調整
	ChangeNextPlayVolumeSoundMem(static_cast<int>(m_bgmVolume * rate), m_nowPlayBgm);

	// 再度再生
	PlaySoundMem(m_nowPlayBgm, DX_PLAYTYPE_BACK, false);
}

void SoundManager::ChangePlaySeVol(int handle, float rate)
{
	LONGLONG soundPos = GetSoundCurrentPosition(handle);

	StopSoundMem(handle);

	SetSoundCurrentTime(soundPos, handle);

	// 音量の調整
	ChangeNextPlayVolumeSoundMem(static_cast<int>(m_seVolume * rate), handle);

	// 再度再生
	PlaySoundMem(handle, DX_PLAYTYPE_BACK, false);
}
