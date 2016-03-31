#pragma once

// 加上 SDKDDKVer.h 可定義最高可用的 Windows 平台。

// 如果要針對先前的 Windows 平台建置應用程式，請加上 WinSDKVer.h，
// 並在加上 SDKDDKVer.h 之前將 _WIN32_WINNT 巨集設為要支援的平台。

#ifdef _WIN64
#define _WIN32_WINNT 0x0601 //WIN7
#else
#define _WIN32_WINNT 0x0501 //WINXP
#endif // _WIN32

#include <WinSDKVer.h>
#include <SDKDDKVer.h>