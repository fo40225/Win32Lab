#pragma once
#include "BaseWindow.h"
#include "BaseWindow.cpp"

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory            *pFactory;
	ID2D1HwndRenderTarget   *pRenderTarget;
	ID2D1SolidColorBrush    *pBrush;
	ID2D1SolidColorBrush    *pClockHandBrush;
	D2D1_ELLIPSE            ellipse;
public:
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT CreateGraphicsResources();
	HRESULT CreateDeviceDependentResources();
	void OnPaint();
	void DiscardGraphicsResources();
	void CalculateLayout();
	void Resize();
	void DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth);
};