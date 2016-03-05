#pragma once

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef struct {

	int stateCode;

} StateInfo;

inline StateInfo* GetAppState(HWND hwnd);