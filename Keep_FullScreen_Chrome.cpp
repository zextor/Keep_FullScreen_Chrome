// Keep_FullScreen_Chrome.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>

void SendFullscreenKey(BYTE Key)
{
	INPUT input;
	memset(&input, 0, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = Key;

	SendInput(1, &input, sizeof(input));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

int main()
{
	LPCTSTR Tray = L"Shell_TrayWnd";
	LPCTSTR Chrome = L"Chrome_RenderWidgetHostHWND";

	HWND h = FindWindow(L"Shell_TrayWnd", NULL);
	if (h != NULL)
	{
		RECT rc;
		GetWindowRect(h, &rc);

		POINT pt;
		pt.x = rc.left + 1;
		pt.y = rc.top + 1;

		while (1)
		{
			HWND Now = WindowFromPoint(pt);

			TCHAR szClass[MAX_PATH];
			GetClassName(Now, szClass, MAX_PATH);

			if (_tcsicmp(szClass, Chrome) == 0) { /* true */ }
			else
			{
				printf("Not Chrome : %S\n", szClass);
				Sleep(1000);
				SendFullscreenKey(VK_F11);
			}
			Sleep(1000);
		}
	}

	return 0;
}