#pragma once
#include "BaseWindow.h"
#include "BaseWindow.cpp"

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory            *pFactory;
	ID2D1HwndRenderTarget   *pRenderTarget;
	ID2D1SolidColorBrush    *pBrush;
	D2D1_ELLIPSE            ellipse;
public:
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT CreateGraphicsResources();
	void OnPaint();
	void DiscardGraphicsResources();
	void CalculateLayout();
};