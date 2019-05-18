#pragma once
#include <map>
#include <string>
#include "BASS\\include\bass.h"
#pragma comment(lib,"BASS\\lib\\bass.lib")

using namespace std;

#define ATA ATBAE::GetInstance()
#define SAMPLING_RATE (44100) //音乐采样率

//AT BASS 音频 引擎
/*采取的是流播放,还有更多的功能*/
class ATBAE
{
	BOOL m_IsInit = FALSE;
	map<string, HSTREAM> m_MusicMap;
	map<string, HSTREAM> m_SoundMap;

	unsigned long m_Volume = 100;
public:
	static ATBAE *GetInstance();
	BOOL InitAudioEngine();
	BOOL UninstallAudioEngine();

	BOOL LoadMusics(string MusicFileName, DWORD Flags = BASS_SAMPLE_LOOP);
	BOOL LoadSounds(string SoundFileName, DWORD Flags = BASS_SAMPLE_MONO);
	BOOL SetVolume(int Volume = 100);
	DWORD GetVolume();
	BOOL VolumeReduce();//--
	BOOL VolumeAdd();//++


	
	BOOL PlayMusics(string MusicFileName,BOOL Restart = TRUE);//TRUE ,从新播放,FALSE 接着播放
	BOOL PlaySounds(string SoundFileName);

	BOOL PauseMusics(string MusicFileName);
	BOOL PauseSounds(string SoundFileName);
	BOOL PauseAllMusics();
	BOOL PauseAllSounds();
	BOOL PauseAllMusicAndSounds();

	BOOL StopMusics(string MusicFileName);
	BOOL StopSounds(string SoundFileName);
	BOOL StopAllMusics();
	BOOL StopAllSounds();
	BOOL StopAllMusicAndSounds();

	void DeleteMusic(string MusicFileName);
	void DeleteSound(string SoundFileName);
	void DeleteAllMusic();
	void DeleteAllSound();
	BOOL FreeATA();
private:
	ATBAE(){}
	~ATBAE();

	//拷贝构造
	ATBAE(const ATBAE& that);
	//同类赋值 重载 = 运算符
	ATBAE& operator = (const ATBAE& that);
};
