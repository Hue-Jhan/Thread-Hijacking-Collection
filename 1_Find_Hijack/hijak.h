#pragma once
#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <winbase.h>

BOOL GetProcess(LPWSTR processName, DWORD* pid, HANDLE* hProcess);

BOOL GetThread(IN DWORD pid, OUT DWORD* tid, OUT HANDLE* hThread);

BOOL HijackThread(IN HANDLE hThread, IN PVOID pAddress);
