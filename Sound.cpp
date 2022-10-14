#include "Sound.h"

IXAudio2MasteringVoice* Sound::pMasteringVoice = NULL;
IXAudio2*				Sound::pXaudio2 = NULL;

#define SAFE_DESTROY(p) { if(p) { (p)->DestroyVoice(); (p)=NULL; } }

Sound::Sound()
{
	HRESULT hr;

	UINT flags = 0;
	//pXaudio2 = NULL;
	
    //
    // Initialize XAudio2
    //
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

	if(pXaudio2 == NULL)
		if( FAILED( hr = XAudio2Create( &pXaudio2, flags ) ) )
			CoUninitialize();

    //
    // Create a mastering voice
    //
    //pMasteringVoice = NULL;

	if(pMasteringVoice == NULL)
		if( FAILED( hr = pXaudio2->CreateMasteringVoice( &pMasteringVoice ) ) )
		{
			SAFE_RELEASE( pXaudio2 );
			CoUninitialize();
		}

	pSourceVoice = NULL;
	pbWaveData = NULL;
}
Sound::~Sound()
{
	if(isRunning())
		pSourceVoice->Stop( 0 );

	SAFE_DESTROY( pSourceVoice );
	SAFE_DELETE_ARRAY( pbWaveData );
}

void Sound::cleanup()
{
	SAFE_RELEASE( pXaudio2 );
}

HRESULT Sound::PlaySound( LPSTR szFilename )
{
    HRESULT hr = S_OK;

    //
    // Read in the wave file
    //
    CWaveFile wav;
    if( FAILED( hr = wav.Open( szFilename, NULL, WAVEFILE_READ ) ) )
        return hr;

    // Get format of wave file
    WAVEFORMATEX* pwfx = wav.GetFormat();

    // Calculate how many bytes and samples are in the wave
    DWORD cbWaveSize = wav.GetSize();

    // Read the sample data into memory
	SAFE_DELETE_ARRAY( pbWaveData );
    pbWaveData = new BYTE[ cbWaveSize ];

    if( FAILED( hr = wav.Read( pbWaveData, cbWaveSize, &cbWaveSize ) ) )
        return hr;

    //
    // Play the wave using a XAudio2SourceVoice
    //

    // Create the source voice
	if( FAILED( hr = pXaudio2->CreateSourceVoice( &pSourceVoice, pwfx ) ) )
		return hr;

    // Submit the wave sample data using an XAUDIO2_BUFFER structure
    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = pbWaveData;
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = cbWaveSize;

    if( FAILED( hr = pSourceVoice->SubmitSourceBuffer( &buffer ) ) )
        return hr;

	//Play the sound
    hr = pSourceVoice->Start( 0 );

    return hr;
}

BOOL Sound::isRunning()
{
    XAUDIO2_VOICE_STATE state;

	if(pSourceVoice != NULL)
		pSourceVoice->GetState( &state );
	else
		return FALSE;

	return (( state.BuffersQueued > 0 ) != 0);
}