//#include "libnet_PlusPlus.h"
#include "PCAP_DDOS.h"
#include "DDOS.h"
void F()
{
	DOS obj;
	obj.InitDos();
	obj.Run();
}
void T_0()
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "T_0��" << i << std::endl;
	}
}
void T_1()
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << "T_1��" << i << std::endl;
	}
}
int main()
{

	//DDOS Ddos("www.baidu.com");
	//Ddos.Run();

	DOS obj;
	obj.InitDos();
	obj.Run();
	

	system("pause");
	return 0;
}
