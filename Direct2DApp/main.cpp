#include <atlbase.h>
#include <atlwin.h>
#include "MainWindow.h"


INT WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, INT)
{
	MainWindow frmMainWindow;
	MSG message;
	BOOL result;

	while (result = GetMessage(&message, 0, 0, 0))
	{
		if (result != -1)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	};

	return 0;
}