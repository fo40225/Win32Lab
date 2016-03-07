# DynamicLinkSystemBuiltinCRT
dynamic link to MSVCRT without dependency with MSVCR\<version\>.dll

----

PRO

run without MS C++ redist

reduce binary file size, memory usage.

if CRT have a security issue, system will update the CRT

CON

system dll didn't have full C++ support (maybe VC6 level?), STL only have limited implement.

e.g. cout is declare in iostream.h

Use pure C is better, but MSCRT is not fully conformant with the C99 standard, too.

----

Release x86 build can run at clean XP SP3 system.

To build this project:

1. Download and install WinDDK 7600.16385.1 on C:\WinDDK\7600.16385.1

    https://www.microsoft.com/en-us/download/details.aspx?id=11800

2. Open this project with VS2015

3. Change solution configuration to release, and choose x86 or x64 which you want

----

You can't build debug version because VS2015 is lack of RunTmChk.lib.

To workaround this:

1. remove RunTmChk.lib from \<AdditionalDependencies\>

2. disable Basic Runtime Checks (\<BasicRuntimeChecks\>Default\</BasicRuntimeChecks\\\>)

----

You can't run debug version because you have to obtain the correct version of msvcirtd.dll, msvcprtd.dll, msvcrtd.dll

System build-in dll version ( wdk lib ver) is not equal to VC6's msvcirtd.dll, msvcprtd.dll, msvcrtd.dll