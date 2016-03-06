#include "stdafx.h"
#include "MainWindow.h"
#include "Utility.h"

PCWSTR MainWindow::ClassName() const { return L"Sample Window Class"; }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (FAILED(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
		{
			return -1;  // Fail CreateWindowEx.
		}
	}
	return 0;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;

	case WM_PAINT:
	{
		OnPaint();
	}
	return 0;

	case WM_SIZE:
	{
		Resize();
	}
	return 0;

	default:
	{
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	}

	return TRUE;
}

HRESULT MainWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			hr = CreateDeviceDependentResources();

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}

	return hr;
}

HRESULT MainWindow::CreateDeviceDependentResources()
{
	HRESULT hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &pClockHandBrush);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0), &pBrush);

	return hr;
}

void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
		pRenderTarget->FillEllipse(ellipse, pBrush);

		// Draw hands
		SYSTEMTIME time;
		GetLocalTime(&time);

		// 60 minutes = 30 degrees, 1 minute = 0.5 degree
		const float fHourAngle = (360.0f / 12) * (time.wHour) + (time.wMinute * 0.5f);
		const float fMinuteAngle = (360.0f / 60) * (time.wMinute);
		const float fSecondAngle =
			(360.0f / 60) * (time.wSecond) + (360.0f / 60000) * (time.wMilliseconds);

		DrawClockHand(0.6f, fHourAngle, 6);
		DrawClockHand(0.85f, fMinuteAngle, 4);
		DrawClockHand(0.85f, fSecondAngle, 1);

		// Restore the identity transformation.
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

void MainWindow::CalculateLayout()
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth)
{
	pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(fAngle, ellipse.point)
		);

	// endPoint defines one end of the hand.
	D2D_POINT_2F endPoint = D2D1::Point2F(
		ellipse.point.x,
		ellipse.point.y - (ellipse.radiusY * fHandLength)
		);

	// Draw a line from the center of the ellipse to endPoint.
	pRenderTarget->DrawLine(
		ellipse.point, endPoint, pClockHandBrush, fStrokeWidth);
}