#pragma once

#include "Header.h"
#include "WaveFile.h"

class Sound
{
private:

public:
	static IXAudio2*				pXaudio2;
	static IXAudio2MasteringVoice*	pMasteringVoice;
    IXAudio2SourceVoice*			pSourceVoice;
	BYTE*							pbWaveData;

	Sound();
	~Sound();
	void cleanup();

	HRESULT PlaySound( LPSTR szFilename );
	BOOL isRunning();
};