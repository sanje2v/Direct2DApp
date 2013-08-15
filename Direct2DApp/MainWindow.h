#include <atlbase.h>
#include <atlwin.h>
#include <d2d1.h>
#include <wrl.h>
#include <atltrace.h>
#include <array>
#include <memory>
#include <algorithm>
#include "Ball.h"

#pragma comment(lib, "d2d1")

using namespace D2D1;
using namespace Microsoft::WRL;
using namespace std;


class MainWindow : public CWindowImpl<MainWindow, CWindow, CWinTraits<WS_OVERLAPPEDWINDOW | WS_VISIBLE> >
{
	#define NUM_OF_BALLS			2U
	#define INCREMENT				5.0f
	#define WINDOW_CLASSNAME		L"MainWindow"
	#define WINDOW_TITLE			L"Direct2D Window"
	#define WINDOW_BKCOLOR			ColorF(ColorF::FloralWhite)

private:
	ComPtr<ID2D1Factory> m_d2d1factory;
	ComPtr<ID2D1HwndRenderTarget> m_d2d1rendertarget;
	array<unique_ptr<Ball>, NUM_OF_BALLS> m_arrballs;
	UINT m_speed;

public:
	DECLARE_WND_CLASS_EX(WINDOW_CLASSNAME, CS_HREDRAW | CS_VREDRAW, -1);

	BEGIN_MSG_MAP(MainWindow)
		MESSAGE_HANDLER(WM_PAINT, PaintHandler)
		MESSAGE_HANDLER(WM_DESTROY, DestroyHandler)
		MESSAGE_HANDLER(WM_SIZE, SizeHandler)
		MESSAGE_HANDLER(WM_DISPLAYCHANGE, DisplayChangedHandler)
		MESSAGE_HANDLER(WM_TIMER, TimerElaspedHandler)
	END_MSG_MAP()

	MainWindow()
	{
		RECT rect;
		D2D1_FACTORY_OPTIONS fo = {};

		#ifdef DEBUG
			fo.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
		#endif

		// Create Direct2D Factory object
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, fo, m_d2d1factory.GetAddressOf());
		CreateDeviceIndependentResources();	// Create render target independent resources
		
		// Create render target window
		Create(nullptr, 0, WINDOW_TITLE);

		GetClientRect(&rect);
		auto size = SizeU(rect.right, rect.bottom);
		// Create render target object
		m_d2d1factory->CreateHwndRenderTarget(RenderTargetProperties(), 
												HwndRenderTargetProperties(m_hWnd, size),
												m_d2d1rendertarget.GetAddressOf());
		
		// Initialize ball objects
		for (int i = 0; i < NUM_OF_BALLS; i++)
		{
			Ball& ball = *m_arrballs[i];
			
			m_arrballs[i].reset(new Ball(m_d2d1rendertarget));
		}

		ApplySettings();				// Apply adjustable settings

		SetTimer(1, m_speed, nullptr);	// Start animation timer		
	}

private:
	void ApplySettings();
	void CreateDeviceDependentResources();
	void CreateDeviceIndependentResources();
	void AdvanceNextState(D2D1_SIZE_F);
	void Draw(D2D1_SIZE_F);

	void Render()
	{
		if (!m_d2d1rendertarget)
		{
			RECT rect;

			GetClientRect(&rect);
			auto size = SizeU(rect.right, rect.bottom);
			m_d2d1factory->CreateHwndRenderTarget(RenderTargetProperties(), 
													HwndRenderTargetProperties(m_hWnd, size),
													m_d2d1rendertarget.GetAddressOf());
			CreateDeviceDependentResources();
		}

		if (!isHidden())
		{
			m_d2d1rendertarget->BeginDraw();

			Draw(m_d2d1rendertarget->GetSize());

			if (m_d2d1rendertarget->EndDraw() == D2DERR_RECREATE_TARGET)
				m_d2d1rendertarget.Reset();
		}
	}

	void Invalidate()
	{
		InvalidateRect(nullptr, FALSE);
	}

	bool isHidden()
	{
		return (D2D1_WINDOW_STATE_OCCLUDED & m_d2d1rendertarget->CheckWindowState()) == D2D1_WINDOW_STATE_OCCLUDED;
	}

	LRESULT PaintHandler(UINT, WPARAM, LPARAM, BOOL &);
	LRESULT DestroyHandler(UINT, WPARAM, LPARAM, BOOL &);
	LRESULT SizeHandler(UINT, WPARAM, LPARAM, BOOL &);
	LRESULT DisplayChangedHandler(UINT, WPARAM, LPARAM, BOOL &);
	LRESULT TimerElaspedHandler(UINT, WPARAM, LPARAM, BOOL &);
};