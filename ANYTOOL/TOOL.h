#pragma once
//����C#��
#include "stdafx.h"
#using "Tool\\CSharPDDOS_DLL\\CSharPDdos.dll"

//���������й�(��Ҫ�ɲ�Ҫ)
#pragma managed

//����ClassLibrary1�����ռ�
using namespace CSharPDdos;




//===========================================================
//������IP,�˿�,�߳���
int Init_CSharP_DLL_To_CPlusPlus_DLL(const char *IP, const int Port, int ThreadNumber);
//ֹͣ����
int Stop_CSharP_DLL_To_CPlusPlus_DLL_DDosAttack();