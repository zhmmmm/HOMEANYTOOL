#pragma once

#define EXPORTDLL       extern"C" _declspec(dllexport)

class WebICAdapter
{
public:
	WebICAdapter(void);
	~WebICAdapter(void);

	int __stdcall add(int p1, int p2);
};

// ��������ʵ��ָ��
EXPORTDLL void* __stdcall classInit(void **clsp);
EXPORTDLL int __stdcall CallClass(WebICAdapter* p, int p1, int p2);


EXPORTDLL int  __stdcall Add(int k);
