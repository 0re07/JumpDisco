#include <DxLib.h>
#include "./SoundMng.h"
#include "SoundApp.h"

/// <param name="isPlayStart">í‚é~å„Ç…ç≈èâÇ©ÇÁçƒê∂Ç∑ÇÈÇ©Åitrue:çƒê∂Ç∑ÇÈ false:çƒê∂ÇµÇ»Ç¢Åj</param>
void SoundApp::PlayOnceSound(std::string key, bool isPlayStart)
{
	PlaySoundMem(lpSoundMng.GetSoundID(key)[0], DX_PLAYTYPE_BACK, isPlayStart);
}

void SoundApp::PlayLoopSound(std::string key, bool isPlayStart)
{
	PlaySoundMem(lpSoundMng.GetSoundID(key)[0], DX_PLAYTYPE_LOOP, isPlayStart);
}

void SoundApp::StopSound(std::string key)
{
	StopSoundMem(lpSoundMng.GetSoundID(key)[0]);
}

SoundApp::SoundApp()
{
}

SoundApp::~SoundApp()
{
}
