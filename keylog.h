#include <Windows.h>

#ifndef KEYLOG_H
#define KEYLOG_H

const char* translateKeyCode(DWORD virtualKeyCode, BOOL shift, BOOL capsLock);

#endif
