#include "InputHandler.hpp"

namespace engine {

	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key > MAX_KEYS) return;

		InputHandler* handler = (InputHandler*)glfwGetWindowUserPointer(window);
		ASSERT(handler != nullptr);

		switch (action) {
		case GLFW_PRESS:
			handler->m_KeysDown[key] = true;
			handler->m_KeysPolled[key] = true;
			break;
		case GLFW_RELEASE:
			handler->m_KeysDown[key] = false;
			handler->m_KeysPolled[key] = false;
			break;
		default:
			break;
		}
	}

	void OnMouseEvent(GLFWwindow* window, int button, int action, int mods) {
		if (button > MAX_BUTTONS) return;

		InputHandler* handler = (InputHandler*)glfwGetWindowUserPointer(window);
		ASSERT(handler != nullptr);

		switch (action) {
		case GLFW_PRESS:
			handler->m_ButtonsDown[button] = true;
			handler->m_ButtonsPolled[button] = true;
			break;
		case GLFW_RELEASE:
			handler->m_ButtonsDown[button] = false;
			handler->m_ButtonsPolled[button] = false;
			break;
		default:
			break;
		}
	}

	InputHandler::InputHandler(GLFWwindow* window) {
		m_Window = window;
		Init();
	}

	void InputHandler::Init() {
		glfwSetKeyCallback(m_Window, OnKeyEvent);
		glfwSetMouseButtonCallback(m_Window, OnMouseEvent);

		glfwSetWindowUserPointer(m_Window, this);

		memset(m_KeysDown, 0, MAX_KEYS);
		memset(m_KeysPolled, 0, MAX_KEYS);
		memset(m_ButtonsDown, 0, MAX_BUTTONS);
		memset(m_ButtonsPolled, 0, MAX_BUTTONS);
	}

	void InputHandler::Update() {
		//TODO check if frames line up
		memset(m_KeysPolled, 0, MAX_KEYS);
		memset(m_ButtonsPolled, 0, MAX_BUTTONS);
	}
}