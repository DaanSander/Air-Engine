#include <iostream>
#include "Window.hpp"
#include "math\Vector2.hpp"
#include "math\Matrix4.hpp"
#include "math\Matrix2.hpp"
#include "system\Path.hpp"
#include "system\File.hpp"
#include "system\Timer.hpp"
#include "system\Logger.hpp"
#include "Common.h"


//TODO Async files
//TODO Create custom STL library 
//TODO Better buffers managing glVertexAttribPointer etc

int32 main() {
	using namespace engine;
	using namespace math;
	using namespace system;

	Logger logger;

	logger.PrintLog(LOG_LEVEL_ERR, true);

	Window* window = new Window("Test", 400, 300);
	Path dir("P:\\Projects\\C++\\Polygon Engine\\Polygon Engine\\Debug\\Window.txt");
	BaseFile* file = new File(dir);
	file->Open(Mode::READ | Mode::BINARY);
	char* data = (char*) file->Read();
	file->Close();
	Timer timer;

	while (!window->ShouldClose()) {
		window->Update();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		if (timer.Elapsed() >= 1.0) {
			timer.Reset();
			std::cout << "Second" << std::endl;
		}
	}

	delete window;
	return 0;
}
