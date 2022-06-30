#pragma once

#include <Windows.h>
#include <windowsx.h>

#include <array>

class c_inputManager {
public:
	void onWndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onWndProcEnd();
	bool isKeyDown(UINT vkCode);
	bool isKeyPressed(UINT vkCode);
	bool isKeyReleased(UINT vkCode);
private:
	UINT m_curKey = 0u;
	bool m_curState = false;

	int m_scrollState = 0;
	POINT m_mousePos = {};

	std::array<bool, 256u> m_keyStates = {};
	std::array<bool, 256u> m_keyStatesOld = {};
};

inline c_inputManager inputManager;
