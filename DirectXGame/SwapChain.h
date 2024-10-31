#pragma once
#include <d3d11.h>

class SwapChain
{
public:

	// Initialize swapchain for a window
	bool init(HWND hwnd, UINT width, UINT height);
	// Release the swap chain
	bool release();
private:
	IDXGISwapChain* m_swap_chain;
};

