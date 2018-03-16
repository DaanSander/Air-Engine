#include "Window.hpp"

namespace engine {
	namespace graphics {

		void Error_Callback(int error, const char* description);
		
		Window::Window(const char* title, unsigned int width, unsigned int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			Init();
		}
		
		Window::~Window() {
			glfwDestroyWindow(m_Window);
			glfwSetErrorCallback(NULL);
		}

		void Window::Init() {
			if (!glfwInit()) {
				glfwTerminate();
				Error_Callback(-1, "Failed to initialize GLFW");
				return;
			}

			glfwSetErrorCallback(Error_Callback);

			glfwDefaultWindowHints();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

			if (!m_Window) {
				Error_Callback(-1, "Failed to create GLFW window");
				return;
			}

			glfwMakeContextCurrent(m_Window);
			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			glfwSwapInterval(1);
		}

		void Window::Update() const {
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		void Error_Callback(int error, const char* description) {
			fprintf(stderr, "Error: %s\n", description);
		}
} }