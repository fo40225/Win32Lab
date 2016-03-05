#pragma once

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;

void InitializeDPIScale(ID2D1Factory *pFactory)
{
	FLOAT dpiX, dpiY;

	pFactory->GetDesktopDpi(&dpiX, &dpiY);

	g_DPIScaleX = dpiX / 96.0f;
	g_DPIScaleY = dpiY / 96.0f;
}

template <typename T>
float PixelsToDipsX(T x)
{
	return static_cast<float>(x) / g_DPIScaleX;
}

template <typename T>
float PixelsToDipsY(T y)
{
	return static_cast<float>(y) / g_DPIScaleY;
}
