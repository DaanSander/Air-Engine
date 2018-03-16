#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

namespace engine {
	namespace graphics {

		class Window {

			GLFWwindow* m_Window;
			int m_Width, m_Height;
			const char* m_Title;
		public: 
			Window(const char* title, unsigned int width, unsigned int height);

			~Window();

			void Update() const;

			inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

			inline unsigned int GetWidth() const { return m_Width; }

			inline unsigned int GetHeight() const { return m_Height; }

			inline const char* GetTitle() const { return m_Title; }

		private:
			friend void Error_Callback(int error, const char* description);

			void Init();
		};
} }