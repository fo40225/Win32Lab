#pragma once

// �[�W SDKDDKVer.h �i�w�q�̰��i�Ϊ� Windows ���x�C

// �p�G�n�w����e�� Windows ���x�ظm���ε{���A�Х[�W WinSDKVer.h�A
// �æb�[�W SDKDDKVer.h ���e�N _WIN32_WINNT �����]���n�䴩�����x�C

#ifdef _WIN64
#define _WIN32_WINNT 0x0601 //WIN7
#else
#define _WIN32_WINNT 0x0501 //WINXP
#endif // _WIN32

#include <WinSDKVer.h>
#include <SDKDDKVer.h>