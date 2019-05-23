#include "Unity.h"


//=========导出函数============
// 返回类别的实例指针
void* __stdcall classInit(void **clsp)
{
	WebICAdapter* p = new WebICAdapter();
	*clsp = p;
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