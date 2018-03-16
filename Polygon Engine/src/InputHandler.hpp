#pragma once

#include <GLFW\glfw3.h>
#include "Common.h"
#include "DataTypes.h"

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

			inline bool KeyDown(uint32 keyCode) const {
				ASSERT(keyCode < MAX_KEYS);
				return m_KeysDown[keyCode];
			}

			inline bool KeyPressed(uint32 keyCode) const {
				ASSERT(keyCode < MAX_KEYS);
				return m_KeysPolled[keyCode];
			}

			inline bool ButtonDown(uint32 button) const {
				ASSERT(button < MAX_BUTTONS);
				return m_ButtonsDown[button];
			}
			
			inline bool ButtonPressed(uint32 button) const {
				ASSERT(button < MAX_BUTTONS);
				return m_ButtonsPolled[button];
			}

		private:
			friend void OnKeyEvent(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods);

			friend void OnMouseEvent(GLFWwindow* window, int32 button, int32 action, int32 mods);
		};
}