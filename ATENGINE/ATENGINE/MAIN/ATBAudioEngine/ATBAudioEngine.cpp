#include "ATBAudioEngine.h"

ATBAE::ATBAE()
{
	ATBAE::InitAudioEngine();
}
ATBAE::ATBAE(const ATBAE& that)
{
	//this->... = than...;
}
ATBAE& ATBAE::operator = (const ATBAE& that)
{
	//this->... = than...;
	return *this;
}


ATBAE::~ATBAE()
{
	ATBAE::FreeATA();
}
ATBAE *ATBAE::GetInstance()
{
	static ATBAE A_T_B_A_E;
	return &A_T_B_A_E;
}

BOOL ATBAE::InitAudioEngine()
{
	if (!m_IsInit)
	{
		if (HIWORD(BASS_GetVersion()) != BASSVERSION)
		{
			return FALSE;
		}
		if (BASS_Init(-1, SAMPLING_RATE, BASS_DEVICE_3D, NULL, NULL))
		{
			m_IsInit = TRUE;
			ATBAE::SetVolume();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL ATBAE::UninstallAudioEngine()
{
	if (m_IsInit)
	{
		return ATBAE::FreeATA();
	}
	return FALSE;
}

BOOL ATBAE::LoadMusics(string MusicFileName, DWORD Flags)
{
	map<string, HSTREAM>::iterator it = m_MusicMap.find(MusicFileName);
	if (it != m_MusicMap.end())//存在
	{
		return TRUE;
	}
	HSTREAM HStream = BASS_StreamCreateFile(FALSE, MusicFileName.c_str(), 0, 0, Flags);//从文件加载音乐
	if (HStream == NULL)
	{
		//加载失败
		return FALSE;
	}
	//make_pair
	m_MusicMap.insert(pair<string, HSTREAM>(MusicFileName, HStream));
	return TRUE;
}

BOOL ATBAE::LoadSounds(string SoundFileName, DWORD Flags)
{
	map<string, HSTREAM>::iterator it = m_SoundMap.find(SoundFileName);
	if (it != m_SoundMap.end())//存在
	{
		return TRUE;
	}
	HSTREAM HStream = BASS_StreamCreateFile(FALSE, SoundFileName.c_str(), 0, 0, Flags);//从文件加载音乐
	if (HStream == NULL)
	{
		//加载失败
		return FALSE;
	}
	//make_pair
	m_SoundMap.insert(pair<string, HSTREAM>(SoundFileName, HStream));
	return TRUE;
}

BOOL ATBAE::SetVolume(int Volume)
{
	if (m_IsInit)
	{
		if (Volume <= 0)
		{
			Volume = 0;
		}
		else if (Volume >= 100)
		{
			Volume = 100;
		}
		m_Volume = (unsigned long)Volume;
		return BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, m_Volume * 100);
	}
	return FALSE;
}

HSTREAM ATBAE::GetStream(string AudioFileName)
{
	if (m_IsInit)
	{
		map<string, HSTREAM>::iterator it = m_MusicMap.find(AudioFileName);
		if (it != m_MusicMap.end())
		{
			return it->second;
		}
		it = m_SoundMap.find(AudioFileName);
		if (it != m_SoundMap.end())
		{
			return it->second;
		}
	}
	return 0;
}

BOOL ATBAE::VolumeReduce()
{
	if (m_IsInit)
	{
		m_Volume -= 1;
		ATBAE::SetVolume(m_Volume);
		return TRUE;
	}
	return FALSE;
}

BOOL ATBAE::VolumeAdd()
{
	if (m_IsInit)
	{
		m_Volume += 1;
		ATBAE::SetVolume(m_Volume);
		return TRUE;
	}
	return FALSE;
}

//=================================================================
DWORD ATBAE::GetAudioStreamData(string AudioFileName, void *Buffer)
{
	if (m_IsInit)
	{
		map<string, HSTREAM>::iterator it = m_MusicMap.find(AudioFileName);
		if (it != m_MusicMap.end())
		{
			return BASS_ChannelGetData(it->second, Buffer, 2147483648);
		}
		it = m_SoundMap.find(AudioFileName);
		if (it != m_SoundMap.end())
		{
			return BASS_ChannelGetData(it->second, Buffer, 2147483648);
		}
	}
	return 0;
}














BOOL ATBAE::PlayMusics(string MusicFileName, BOOL Restart)
{
	map<string, HSTREAM>::iterator it = m_MusicMap.find(MusicFileName);
	if (it != m_MusicMap.end())//存在
	{
		BASS_ChannelPlay(it->second, Restart);
		m_CurPlayMusic = MusicFileName;
		m_IsPlayMusic = TRUE;
		return TRUE;
	}
	if (ATBAE::LoadMusics(MusicFileName))
	{
		ATBAE::PlayMusics(MusicFileName);
	}
	else
	{
		return FALSE;
	}
	//这个return 只是消除警告,没有实际意义
	return TRUE;
}
BOOL ATBAE::PlayMusics_s(string MusicFileName, BOOL Restart)
{
	if (!m_IsPlayMusic)
	{
		return ATBAE::PlayMusics(MusicFileName, Restart);
	}
	return FALSE;
}
BOOL ATBAE::PlaySounds(string SoundFileName)
{
	map<string, HSTREAM>::iterator it = m_SoundMap.find(SoundFileName);
	if (it != m_SoundMap.end())//存在
	{
		BASS_ChannelPlay(it->second, TRUE);
		return TRUE;
	}
	if (ATBAE::LoadSounds(SoundFileName))
	{
		ATBAE::PlaySounds(SoundFileName);
	}
	else
	{
		return FALSE;
	}
	//这个return 只是消除警告,没有实际意义
	return TRUE;
}
BOOL ATBAE::PlayStream(HSTREAM HStream, BOOL Restart)
{
	if (m_IsInit)
	{
		return BASS_ChannelPlay(HStream, Restart);
	}
	return FALSE;
}

BOOL ATBAE::PauseMusics(string MusicFileName)
{
	if (m_IsInit && m_IsPlayMusic)
	{
		map<string, HSTREAM>::iterator it = m_MusicMap.find(MusicFileName);
		if (it != m_MusicMap.end())
		{
			return BASS_ChannelPause(it->second);
		}
	}
	return FALSE;
}
BOOL ATBAE::PauseSounds(string SoundFileName)
{
	if (m_IsInit)
	{
		map<string, HSTREAM>::iterator it = m_SoundMap.find(SoundFileName);
		if (it != m_SoundMap.end())
		{
			return BASS_ChannelPause(it->second);
		}
	}
	return FALSE;
}
BOOL ATBAE::PauseAllMusics()
{
	if (m_IsInit)
	{
		if (!m_MusicMap.empty())
		{
			for (map<string, HSTREAM>::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it++)
			{
				BASS_ChannelPause(it->second);
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ATBAE::PauseAllSounds()
{
	if (m_IsInit)
	{
		if (!m_SoundMap.empty())
		{
			for (map<string, HSTREAM>::iterator it = m_SoundMap.begin(); it != m_SoundMap.end(); it++)
			{
				BASS_ChannelPause(it->second);
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ATBAE::PauseAllMusicAndSounds()
{
	BOOL Music = ATBAE::PauseAllMusics();
	BOOL Sound = ATBAE::PauseAllSounds();
	if (Music && Sound)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL ATBAE::StopMusics(string MusicFileName)
{
	if (m_IsInit && m_IsPlayMusic)
	{
		map<string, HSTREAM>::iterator it = m_MusicMap.find(MusicFileName);
		if (it != m_MusicMap.end())
		{
			return BASS_ChannelStop(it->second);
		}
	}
	return FALSE;
}
BOOL ATBAE::StopSounds(string SoundFileName)
{
	if (m_IsInit)
	{
		map<string, HSTREAM>::iterator it = m_SoundMap.find(SoundFileName);
		if (it != m_SoundMap.end())
		{
			return BASS_ChannelStop(it->second);
		}
	}
	return FALSE;
}
BOOL ATBAE::StopAllMusics()
{
	if (m_IsInit)
	{
		if (!m_MusicMap.empty())
		{
			for (map<string, HSTREAM>::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it++)
			{
				BASS_ChannelStop(it->second);
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ATBAE::StopAllSounds()
{
	if (m_IsInit)
	{
		if (!m_SoundMap.empty())
		{
			for (map<string, HSTREAM>::iterator it = m_SoundMap.begin(); it != m_SoundMap.end(); it++)
			{
				BASS_ChannelStop(it->second);
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL ATBAE::StopAllMusicAndSounds()
{
	BOOL Music = ATBAE::StopAllMusics();
	BOOL Sound = ATBAE::StopAllSounds();
	if (Music && Sound)
	{
		return TRUE;
	}
	return FALSE;
}


void ATBAE::DeleteMusic(string MusicFileName)
{
	ATBAE::StopMusics(MusicFileName);
	map<string, HSTREAM>::iterator it = m_MusicMap.find(MusicFileName);
	if (it != m_MusicMap.end())
	{
		BOOL Free = BASS_StreamFree(it->second);
		m_MusicMap.erase(it);
	}
}
void ATBAE::DeleteSound(string SoundFileName)
{
	map<string, HSTREAM>::iterator it = m_SoundMap.find(SoundFileName);
	if (it != m_SoundMap.end())
	{
		BOOL Free = BASS_StreamFree(it->second);
		m_SoundMap.erase(it);
	}
}
void ATBAE::DeleteAllMusic()
{
	if (!m_MusicMap.empty())
	{
		for (map<string, HSTREAM>::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it++)
		{
			BASS_StreamFree(it->second);
		}
		m_MusicMap.clear();
	}
}
void ATBAE::DeleteAllSound()
{
	if (!m_SoundMap.empty())
	{
		for (map<string, HSTREAM>::iterator it = m_SoundMap.begin(); it != m_SoundMap.end(); it++)
		{
			BASS_StreamFree(it->second);
		}
		m_SoundMap.clear();
	}
}
void ATBAE::DeleteAllMusicAndSounds()
{
	ATBAE::DeleteAllMusic();
	ATBAE::DeleteAllSound();
}
BOOL ATBAE::FreeATA()
{
	if (m_IsInit)
	{
		ATBAE::StopAllMusicAndSounds();

		ATBAE::DeleteAllMusic();
		ATBAE::DeleteAllSound();
		BASS_Free();
		m_IsInit = FALSE;
		return TRUE;
	}
	return FALSE;
}


double ATBAE::GetTimeSecond(string MusicFileName)
{
	if (m_IsInit)
	{
		HSTREAM Stream = ATBAE::GetStream(MusicFileName);
		unsigned __int64 StreamLen = BASS_ChannelGetLength(Stream, BASS_POS_BYTE);
		return BASS_ChannelBytes2Seconds(Stream, StreamLen);
	}
	return 0;
}
double ATBAE::GetTimeMinute(string MusicFileName)
{
	return ATBAE::GetTimeSecond(MusicFileName) / 60.0;
}
double ATBAE::GetTimeHour(string MusicFileName)
{
	return ATBAE::GetTimeMinute(MusicFileName) / 60.0;
}
double ATBAE::GetCurTimeSecond(string MusicFileName)
{
	if (m_IsInit)
	{
		HSTREAM Stream = ATBAE::GetStream(MusicFileName);
		return BASS_ChannelBytes2Seconds(Stream, BASS_ChannelGetPosition(Stream, BASS_POS_BYTE));
	}
	return 0;
}
double ATBAE::GetCurTimeMinute(string MusicFileName)
{
	return ATBAE::GetCurTimeSecond(MusicFileName) / 60.0;
}
double ATBAE::GetCurTimeHour(string MusicFileName)
{
	return ATBAE::GetCurTimeMinute(MusicFileName) / 60.0;
}
unsigned __int64 ATBAE::GetCurPoint(string MusicFileName)
{
	if (m_IsInit)
	{
		return BASS_ChannelGetPosition(ATBAE::GetStream(MusicFileName), BASS_POS_BYTE);
	}
	return 0;
}
BOOL ATBAE::SetTimeSecond(string MusicFileName, double Second)
{
	if (m_IsInit)
	{
		HSTREAM Stream = ATBAE::GetStream(MusicFileName);
		unsigned __int64 CurPoint = BASS_ChannelSeconds2Bytes(Stream, Second);
		ATBAE::PauseMusics(MusicFileName);
		if (BASS_ChannelSetPosition(Stream, CurPoint, BASS_POS_BYTE))
		{
			return ATBAE::PlayMusics(MusicFileName, FALSE);
		}
	}
	return FALSE;
}
BOOL ATBAE::SetTimeMinute(string MusicFileName, double Minute)
{
	return ATBAE::SetTimeSecond(MusicFileName, Minute * 60.0);
}
BOOL ATBAE::SetTimeHour(string MusicFileName, double Hour)
{
	return ATBAE::SetTimeMinute(MusicFileName, Hour * 60.0);
}