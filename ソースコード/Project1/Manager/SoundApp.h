#pragma once
#include <string>

#define lpSoundApp SoundApp::GetInstanse()

class SoundApp
{
public:
	//静的コンストラクタ（常に必要）
	static SoundApp& GetInstanse()
	{
		static SoundApp sApp_Instance;
		return sApp_Instance;
	}

	//音の再生
	void PlayOnceSound(std::string key, bool isPlayStart);	//一度だけ再生			
	void PlayLoopSound(std::string key, bool isPlayStart);	//ループ再生

	void PauseSound(std::string key);						//一時停止
	void StopSound(std::string key);						//停止
	void ChengeVolumeSound(std::string key, int valume);	//音量変更

private:
	SoundApp();
	~SoundApp();

};

