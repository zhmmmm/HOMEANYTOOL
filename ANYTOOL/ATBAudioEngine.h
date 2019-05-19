#pragma once
#include <map>
#include <string>
#include "BASS\\include\\bass.h"
#pragma comment(lib,"BASS\\lib\\bass.lib")

using namespace std;

#define ATA ATBAE::GetInstance()
#define SAMPLING_RATE (44100) //���ֲ�����

//AT BASS ��Ƶ ����
/*��ȡ����������,���и���Ĺ���*/
class ATBAE
{
	//�Ƿ��ʼ��
	BOOL m_IsInit = FALSE;
	//����Map
	map<string, HSTREAM> m_MusicMap;
	//��ЧMap
	map<string, HSTREAM> m_SoundMap;

	//����
	unsigned long m_Volume = 100;
	BOOL m_IsPlayMusic = FALSE;
public:
	static ATBAE *GetInstance();
	BOOL InitAudioEngine();
	BOOL UninstallAudioEngine();

	BOOL LoadMusics(string MusicFileName, DWORD Flags = BASS_SAMPLE_LOOP);
	BOOL LoadSounds(string SoundFileName, DWORD Flags = BASS_SAMPLE_MONO);
	BOOL SetVolume(int Volume = 100);
	DWORD GetVolume() { return m_Volume; }
	HSTREAM GetStream(string AudioFileName);
	BOOL VolumeReduce();//--
	BOOL VolumeAdd();//++
	//=================================================================
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	/*
	static int W = 3;
	static int WSpace = 1;
	static int Y = 190;
	void Scene::Update()
	{
		ATA->PlayMusics_s("res\\Audio\\Musics\\ҹɫ.flac");
		Camera::CameraToWorld(this);
		this->m_CameraPos_Y = 0;
		//AT->CreateQuadrangle(
		//	ATATRGB::RED, ATATPOS3D(-105, +205, 0),
		//	ATATRGB::WHITE, ATATPOS3D(-105, -105, 0),
		//	ATATRGB::WHITE, ATATPOS3D(+105, -105, 0),
		//	ATATRGB::RED, ATATPOS3D(+105, +105, 0));
		//AT->DrawEnd();
		int X = -200;
		static float Buf[128] = { 0 };
		ATA->GetAudioStreamData("res\\Audio\\Musics\\ҹɫ.flac", Buf);
		for (int i = 0; i < 128; i++)
		{
			Y = Buf[i] * 1000;

			AT->CreateQuadrangle(
				ATATRGB::RED, ATATPOS3D(X, Y, 0),
				ATATRGB::WHITE, ATATPOS3D(X, 0, 0),
				ATATRGB::WHITE, ATATPOS3D(X + W, 0, 0),
				ATATRGB::RED, ATATPOS3D(X + W,Y, 0));
			X = X + W + WSpace;
			Y = 190;
		}
		AT->DrawEnd();
		ZeroMemory(Buf,128);
	}
	*/
	/*
		char Buf[128];
		while (true)
		{
			ATA->GetAudioStreamData("ҹɫ.flac",Buf);
			system("cls");
			printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", Buf[0], Buf[1], Buf[2], Buf[3], Buf[4], Buf[5], Buf[6], Buf[7], Buf[8], Buf[9]);
			int end = 0;
		}
	*/
	DWORD GetAudioStreamData(string AudioFileName, void *Buffer);






	//TRUE ,���²���,FALSE ���Ų���
	BOOL PlayMusics(string MusicFileName, BOOL Restart = TRUE);
	BOOL PlayMusics_s(string MusicFileName, BOOL Restart = TRUE);
	BOOL PlaySounds(string SoundFileName);
	BOOL PlayStream(HSTREAM HStream, BOOL Restart = TRUE);

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
	void DeleteAllMusicAndSounds();
	BOOL FreeATA();
	//=================================================================
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	//������
	double GetTimeSecond(string MusicFileName);
	//���ط�
	double GetTimeMinute(string MusicFileName);
	//����ʱ
	double GetTimeHour(string MusicFileName);
	//������
	double GetCurTimeSecond(string MusicFileName);
	//���ط�
	double GetCurTimeMinute(string MusicFileName);
	//����ʱ
	double GetCurTimeHour(string MusicFileName);
	//����ָ���ָ��λ��::::::::::::::::::::::::::
	unsigned __int64 GetCurPoint(string MusicFileName);
	//������
	BOOL SetTimeSecond(string MusicFileName, double Second);
	//���÷�
	BOOL SetTimeMinute(string MusicFileName, double Minute);
	//����ʱ
	BOOL SetTimeHour(string MusicFileName, double Hour);


private:
	ATBAE();
	~ATBAE();

	//��������
	ATBAE(const ATBAE& that);
	//ͬ�ำֵ ���� = �����
	ATBAE& operator = (const ATBAE& that);
};