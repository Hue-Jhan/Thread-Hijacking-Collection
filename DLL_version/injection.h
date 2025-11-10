#pragma once
#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <winbase.h>

BOOL GetThread(IN DWORD dwProcessId, OUT DWORD* dwThreadId, OUT HANDLE* hThread);

BOOL HijackThread(IN HANDLE hThread, IN PVOID pAddress);

VOID temp(VOID);
