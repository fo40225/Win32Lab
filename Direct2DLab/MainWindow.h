#pragma once
#include "BaseWindow.h"
#include "BaseWindow.cpp"

class MainWindow : public BaseWindow<MainWindow>
{
public:
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
