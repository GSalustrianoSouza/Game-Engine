#include "Window.h"

Window* window = nullptr;

Window::Window()
{
	// TODO: implement later
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			// Event fired when the window will be created
			//Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			//SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window);
			window->setHWND(hwnd);
			window->onCreate();
			break;
		}

		case WM_DESTROY:
		{
			// Event fired when the window will be destroyed
			//Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
			window->onDestroy();
			::PostQuitMessage(0);
			break;
		}

		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;

	if (!::RegisterClassEx(&wc)) // If register class fail, return false
		return false;

	if (!window)
		window = this;

	// Creation of the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	// If creation window fail, return false
	if (!m_hwnd)
		return false;

	//Show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// Set this flag to indicate that the window is initialized and running
	m_is_run = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->onUpdate();

	Sleep(0);

	return true;
}

bool Window::release()
{
	// Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
	// TODO: implement later
}

void Window::onUpdate()
{
	// TODO: implement later
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{
	// TODO: implement later
}
