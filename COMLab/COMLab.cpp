#include "stdafx.h"
#include "COMLab.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow
	)
{
	throw_if_fail(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE));

	CComPtr<IFileOpenDialog> pFileOpen;

	// Create the FileOpenDialog object.
	throw_if_fail(pFileOpen.CoCreateInstance(__uuidof(FileOpenDialog)));

	// Show the Open dialog box.
	throw_if_fail(pFileOpen->Show(NULL));

	// Get the file name from the dialog box.
	CComPtr<IShellItem> pItem;
	throw_if_fail(pFileOpen->GetResult(&pItem));

	PWSTR pszFilePath;
	throw_if_fail(pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath));

	// Display the file name to the user.
	MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
	CoTaskMemFree(pszFilePath);

	CoUninitialize();
	return 0;
}

inline void throw_if_fail(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw _com_error(hr);
	}
}