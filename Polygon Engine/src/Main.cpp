#include <iostream>
#include "graphics\Window.hpp"
#include "math\Vector2.hpp"
#include "math\Matrix4.hpp"
#include "math\Matrix2.hpp"
#include "system\Path.hpp"
#include "system\File.hpp"

//TODO Async files
//TODO Create custom STL library 

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace math;
	using namespace system;

	Window* window = new Window("Test", 400, 300);
	Path dir("P:\\Projects\\C++\\Polygon Engine\\Polygon Engine\\Debug\\Window.txt");
	BaseFile* file = new File(dir);
	file->Open(Mode::READ | Mode::BINARY);
	char* data = (char*) file->Read();
	file->Close();

	while (!window->ShouldClose()) {
		window->Update();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}

	delete window;
	return 0;
}