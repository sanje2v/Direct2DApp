#include "MainWindow.h"


LRESULT MainWindow::PaintHandler(UINT, WPARAM, LPARAM, BOOL &)
{
	PAINTSTRUCT ps;

	BeginPaint(&ps);
	Render();
	EndPaint(&ps);

	return 0;
}

LRESULT MainWindow::DestroyHandler(UINT, WPARAM, LPARAM, BOOL &)
{
	PostQuitMessage(0);

	return 0;
}

LRESULT MainWindow::SizeHandler(UINT, WPARAM, LPARAM lparam, BOOL &)
{
	if (m_d2d1rendertarget)
		if (m_d2d1rendertarget->Resize(SizeU(LOWORD(lparam), HIWORD(lparam))) != S_OK)
			m_d2d1rendertarget.Reset();

	return 0;
}

LRESULT MainWindow::DisplayChangedHandler(UINT, WPARAM, LPARAM, BOOL &)
{
	Invalidate();

	return 0;
}

LRESULT MainWindow::TimerElaspedHandler(UINT, WPARAM, LPARAM, BOOL &)
{
	if (m_d2d1rendertarget)
	{
		AdvanceNextState(m_d2d1rendertarget->GetSize());
		Invalidate();
	}

	return 0;
}