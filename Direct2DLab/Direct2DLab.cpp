#include "stdafx.h"
#include "Direct2DLab.h"
#include "MainWindow.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow
	)
{
	if (!InitializeTimer())
	{
		return 0;
	}


	MainWindow win;

	if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	// Run the message loop.

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		// Wait until the timer expires or any message is posted.
		if (MsgWaitForMultipleObjects(1, &g_hTimer, FALSE, INFINITE, QS_ALLINPUT)
			== WAIT_OBJECT_0)
		{
			InvalidateRect(win.Window(), NULL, FALSE);
		}
	}

	return 0;
}

BOOL InitializeTimer()
{
	g_hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (g_hTimer == NULL)
	{
		return FALSE;
	}

	LARGE_INTEGER li = {};

	if (!SetWaitableTimer(g_hTimer, &li, (1000 / 60), NULL, NULL, FALSE))
	{
		CloseHandle(g_hTimer);
		g_hTimer = NULL;
		return FALSE;
	}

	return TRUE;
}