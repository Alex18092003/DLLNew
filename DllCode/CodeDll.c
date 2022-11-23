#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "../DLLNew/Header.h"


BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD dwReason,      // причина вызова функции
	LPVOID ipReserved)
{
	BOOL ballWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Инициализируйте один раз для каждого нового процесса.
		// Верните значение FALSE для сбоя загрузки DLL.
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (ballWentWell)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


int  GetRowCountData() // досчет строк 
{
	HANDLE fileStart;
	// открываемый файл, для чтения, для совместного чтения, защита по умолчанию,только существующий файл,обычный файл,атрибутов шаблона нет   
	fileStart = CreateFile(L"C:\\Users\\лебедевааф\\source\\repos\\SistDll\\DllCode\\Users.csv", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileStart == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При открытие файла возникла ошибка!", L"Окно ошибки", MB_OK);
		return 0;
	}
	DWORD d;
	char* str = calloc(100000, 1);
	ReadFile(fileStart, str, 100000, &d, NULL);
	CloseHandle(fileStart);
	int i = 0;
	int count = 0;
	while (i != 100000)
	{
		if (str[i] == '\n')
		{
			count++; // считаем количество строк
		}
		i++;
	}
	return count;
}
//парсим
int GetParse(char* str, user* Users, int* count)
{
	int j = 0;
	int i = 0;
	int k = 0;
	char* stroka = calloc(100, 1);
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
		}
		else
		{
			while (str[i] != ';')
			{
				stroka[j] = str[i];
				j++;
				i++;
			}
			i++;
			Users[k].surname = calloc(j + 1, sizeof(char));
			strncpy(Users[k].surname, stroka, j);
			free(stroka);
			stroka = calloc(100, 1);
			j = 0;
			while (str[i] != ';')
			{
				stroka[j] = str[i];
				j++;
				i++;
			}
			Users[k].name = calloc(j + 1, sizeof(char));
			strncpy(Users[k].name, stroka, j);
			free(stroka);
			stroka = calloc(100, 1);
			j = 0;
			while (str[i] != ';')
			{
				stroka[j] = str[i];
				j++;
				i++;
			}
			i++;
			Users[k].patronomic = calloc(j + 1, sizeof(char));
			strncpy(Users[k].patronomic, stroka, j);
			free(stroka);
			stroka = calloc(100, 1);
			j = 0;
			while (str[i] != '\"')
			{
				stroka[j] = str[i];
				j++;
				i++;
			}
			i++;
			Users[k].age = atoi(stroka);
			free(stroka);
			stroka = calloc(100, 1);
			j = 0;
			i += 2;
			k++;

		}
	}
	*count = k;
}

user* ReadData(user* Users, int* count)
{
	HANDLE fileStart;
	// открываемый файл, для чтения, для совместного чтения, защита по умолчанию,только существующий файл,обычный файл,атрибутов шаблона нет   
	fileStart = CreateFile(L"C:\\Users\\лебедевааф\\source\\repos\\SistDll\\DllCode\\Users.csv", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileStart == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При открытие файла возникла ошибка!", L"Окно ошибки", MB_OK);
		return 0;
	}
	DWORD d;
	char* str = calloc(100000, 1);
	ReadFile(fileStart, str, 100000, &d, NULL);
	CloseHandle(fileStart);
	GetParse(str, Users, count);
	return Users;
}

void WriteData(user* Users, int count)
{
	HANDLE fileRezurt;
	fileRezurt = CreateFile(L"..\\Rezult.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	DWORD d;
	int i = 0;
	char* str;
	while (i != count)
	{
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].surname);
		WriteFile(fileRezurt, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].name);
		WriteFile(fileRezurt, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%s;", Users[i].patronomic);
		WriteFile(fileRezurt, str, strlen(str), &d, NULL);
		free(str);
		str = calloc(100, sizeof(char));
		sprintf(str, "%d\n", Users[i].age);
		WriteFile(fileRezurt, str, strlen(str), &d, NULL);
		i++;
	}
	CloseHandle(fileRezurt);
}

//функция для нахождения среднего возраста некоторого количества пользователей.
void MiddleAge(user* Users, int count)
{
	int i = 0;
	int summa = 0;
	while (i != count)
	{
		summa += Users[i].age;
		i++;
	}
	double SrednAge = (double)summa / (double)count;
	HANDLE fileRezurt;
	fileRezurt = CreateFile(L"..\\Rezult.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileRezurt == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"При записи файла возникла ошибка!", L"Окно ошибки", MB_OK);
		return 0;
	}
	DWORD d;
	char* str = calloc(100000, sizeof(char));
	sprintf(str, "Средний возраст = %f", SrednAge);
	//ovelapf.Offset = 0xFFFFFFFF;
	//ovelapf.OffsetHigh = 0xFFFFFFFF;
	WriteFile(fileRezurt, str, strlen(str), &d, NULL);
	CloseHandle(fileRezurt);
}
