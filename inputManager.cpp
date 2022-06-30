#include "inputManager.h"

void c_inputManager::onWndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam) {

	m_curKey = 0;
	m_curState = false;

	switch (uMsg)
	{
	case WM_MOUSEMOVE: {

		m_mousePos.x = GET_X_LPARAM(lParam);
		m_mousePos.y = GET_Y_LPARAM(lParam);

		return;
	}
	case WM_MOUSEWHEEL: {

		m_scrollState = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		return;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: {

		if (wParam < 256U) {

			m_curKey = static_cast<UINT>(wParam);
			m_curState = true;
		}

		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP: {

		if (wParam < 256U) {

			m_curKey = static_cast<UINT>(wParam);
			m_curState = false;
		}

		break;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: {

		m_curKey = VK_LBUTTON;
		m_curState = uMsg == WM_LBUTTONUP ? false : true;

		break;
	}
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP: {

		m_curKey = VK_RBUTTON;
		m_curState = uMsg == WM_RBUTTONUP ? false : true;

		break;
	}
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP: {

		m_curKey = VK_MBUTTON;
		m_curState = uMsg == WM_MBUTTONUP ? false : true;

		break;
	}
	default:
		break;
	}

	if (m_curKey != 0) 
		m_keyStates.at(m_curKey) = m_curState;
}

void c_inputManager::onWndProcEnd() {

	if (m_curKey != 0)
		m_keyStatesOld.at(m_curKey) = m_keyStates.at(m_curKey);

	m_scrollState = 0;
}

bool c_inputManager::isKeyDown(UINT vkCode) {
	
	return m_keyStates.at(vkCode) == true;
}

bool c_inputManager::isKeyPressed(UINT vkCode) {

	return m_keyStates.at(vkCode) == true && m_keyStatesOld.at(vkCode) == false;
}

bool c_inputManager::isKeyReleased(UINT vkCode) {

	return m_keyStates.at(vkCode) == false && m_keyStatesOld.at(vkCode) == true;
}