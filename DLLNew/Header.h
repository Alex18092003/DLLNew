#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>

struct us
{
	char* surname;
	char* name;
	char* patronomic;
	int age;
};
typedef struct us user;

typedef int(_cdecl* MyFinctionCount)();
typedef user* (_cdecl* MyFunctionRead)(user*, int*);
typedef void(_cdecl* MyFunctionWrite)(user*, int);
typedef user* (_cdecl* MyFunctionSearch)(char*, user*, int, int*);
typedef void(_cdecl* MyFunctionSr)(user*, int);


__declspec(dllexport) int GetRowCountData();
__declspec(dllexport) user* ReadData(user* Users, int* count);

__declspec(dllexport) void WriteData(user* Users, int count);

__declspec(dllexport) user* LastNameSearch(char* str, user* Users, int count, int* kolSurname);
__declspec(dllexport) void MiddleAge(user* Users, int count);

