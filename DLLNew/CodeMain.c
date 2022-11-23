#include <Windows.h>
#include "Header.h"
#define PATH "C:\\Users\\лебедевааф\\source\\repos\\DLLNew\\Debug\\DllCode.dll"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	//проверка запуска 
	//if (!(hMyDLL = LoadLibrary(PATH))) return 1;
	if ((hMyDLL = LoadLibraryA(PATH)) == NULL) return 11;


	MyFinctionCount myFunkCount = (MyFinctionCount)GetProcAddress(hMyDLL, "GetRowCountData");
	user* Users = calloc(myFunkCount(), sizeof(user));
	int count = 0;
	//считывание
	MyFunctionRead myFunRead = (MyFunctionRead)GetProcAddress(hMyDLL, "ReadData");
	Users = myFunRead(Users, &count);
	int kolvan = 0;
	// ср возраст
	MyFunctionSr myFunSr = (MyFunctionSr)GetProcAddress(hMyDLL, "MiddleAge");
	myFunSr(Users, kolvan);
	//вывод
	MyFunctionWrite myFunkWrite = (MyFunctionWrite)GetProcAddress(hMyDLL, "WriteData");
	myFunkWrite(Users, kolvan);

	FreeLibrary(hMyDLL);

	return 0;
}
