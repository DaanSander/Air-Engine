#pragma once

#include "Common.h"
#include <GLFW\glfw3.h>

#define MAX_KEYS 125
#define MAX_BUTTONS 5

namespace engine {


		class InputHandler {
			bool m_KeysDown[MAX_KEYS];
			bool m_ButtonsDown[MAX_BUTTONS];

			bool m_KeysPolled[MAX_KEYS];
			bool m_ButtonsPolled[MAX_BUTTONS];

			GLFWwindow* m_Window;

			friend class Window;

			InputHandler(GLFWwindow* window);

			void Update();

			void Init();
		public:

			inline bool KeyDown(unsigned int keyCode) const {
				ASSERT(keyCode < MAX_KEYS);
				return m_KeysDown[keyCode];
			}

			inline bool KeyPressed(unsigned int keyCode) const {
				ASSERT(keyCode < MAX_KEYS);
				return m_KeysPolled[keyCode];
			}

			inline bool ButtonDown(unsigned int button) const {
				ASSERT(button < MAX_BUTTONS);
				return m_ButtonsDown[button];
			}
			
			inline bool ButtonPressed(unsigned int button) const {
				ASSERT(button < MAX_BUTTONS);
				return m_ButtonsPolled[button];
			}

		private:
			friend void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

			friend void OnMouseEvent(GLFWwindow* window, int button, int action, int mods);
		};
}