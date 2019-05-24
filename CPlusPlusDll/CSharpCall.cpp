#include "CSharpCall.h"

#define SAMPLING_RATE (44100) //音乐采样率
//=========导出函数============
// 返回类别的实例指针
void* __stdcall classInit(void *clsp)
{
	WebICAdapter* p = new WebICAdapter();
	clsp = p;
	return clsp;
}
int __stdcall CallClass(WebICAdapter* p, int p1, int p2)
{
	return p->add(p1, p2);
}
//==========类别实现===========
WebICAdapter::WebICAdapter(void)
{
}
WebICAdapter::~WebICAdapter(void)
{
}

int __stdcall WebICAdapter::add(int p1, int p2)
{

	return p1 * p2;
}




 int __stdcall Add(int k)
{
	 int a = 123 + k;
	return a;
}

 //======================================================
 BOOL __stdcall InitAudioEngine()
 {
	 if (HIWORD(BASS_GetVersion()) != BASSVERSION)
	 {
		 return FALSE;
	 }
	 if (BASS_Init(-1, 44100, BASS_DEVICE_3D, NULL, NULL))
	 {
		 return TRUE;
	 }
	 return FALSE;
 }
 BOOL __stdcall UninstallAudioEngine()
 {
	 return BASS_Free();
 }
 BOOL __stdcall SetVolume(int Volume)
 {
	 return BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, Volume * 100);
 }
 HSTREAM __stdcall LoadMusics(char *MusicFileName)
 {
	 HSTREAM HStream = BASS_StreamCreateFile(FALSE, MusicFileName, 0, 0, BASS_SAMPLE_LOOP);//从文件加载音乐
	 return HStream;
 }
 BOOL __stdcall PlayMusics(long  MusicFileName)
 {
	 return BASS_ChannelPlay((HSTREAM)MusicFileName, TRUE);
 }
 BOOL __stdcall PauseMusics(long MusicFileName)
 {
	 return BASS_ChannelPause((HSTREAM)MusicFileName);
 }