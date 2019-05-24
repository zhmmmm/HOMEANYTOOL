#pragma once
#include "bass.h"
#define EXPORTDLL       extern"C" _declspec(dllexport)
#pragma comment(lib,"bass.lib")
class WebICAdapter
{
public:
	WebICAdapter(void);
	~WebICAdapter(void);

	int __stdcall add(int p1, int p2);
};

// 返回类别的实例指针
EXPORTDLL void* __stdcall classInit(void *clsp);
EXPORTDLL int __stdcall CallClass(WebICAdapter* p, int p1, int p2);


EXPORTDLL int  __stdcall Add(int k);




EXPORTDLL	BOOL __stdcall InitAudioEngine();
EXPORTDLL	BOOL __stdcall UninstallAudioEngine();
EXPORTDLL BOOL __stdcall SetVolume(int Volume = 100);
EXPORTDLL	HSTREAM __stdcall LoadMusics(char *MusicFileName);
EXPORTDLL	BOOL __stdcall PlayMusics(long MusicFileName);
EXPORTDLL	BOOL __stdcall PauseMusics(long MusicFileName);
