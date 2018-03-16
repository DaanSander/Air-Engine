#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include "InputHandler.hpp"

namespace engine {

		class Window {

			GLFWwindow* m_Window;
			int32 m_Width, m_Height;
			const char* m_Title;
			InputHandler* m_InputHandler;

		public: 
			Window(const char* title, uint32 width, uint32 height);

			~Window();

			void Update() const;

			inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

			inline uint32 GetWidth() const { return m_Width; }

			inline uint32 GetHeight() const { return m_Height; }

			inline const char* GetTitle() const { return m_Title; }

			inline const InputHandler* GetInputHandler() const { return m_InputHandler;  }

		private:
			friend void Error_Callback(int32 error, const char* description);

			void Init();
		};
}