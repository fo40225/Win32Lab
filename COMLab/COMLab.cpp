#include "stdafx.h"
#include "COMLab.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow
	)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		// The function succeeded.

		CComPtr<IFileOpenDialog> pFileOpen;

		// Create the FileOpenDialog object.
		hr = pFileOpen.CoCreateInstance(__uuidof(FileOpenDialog));
		if (SUCCEEDED(hr))
		{
			// Use the FileOpenDialog object.

			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				CComPtr<IShellItem> pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
						CoTaskMemFree(pszFilePath);
					}
				}
			}
		}
		else
		{
			// An error occurred.
			return hr;
		}

		CoUninitialize();
		return 0;
	}
	else
	{
		// Handle the error.
		return hr;
	}
}