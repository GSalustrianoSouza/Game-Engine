#include "AppWindow.h"

AppWindow::AppWindow()
{
	// TODO: implement later
}

AppWindow::~AppWindow()
{
	// TODO: implement later
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::get()->release();
}