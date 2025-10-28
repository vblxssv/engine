#include "application/Application.h"



int main(int argc, char** argv) {
	Application app(1200, 800, argv[0]);
	if (!app.init()) {
		std::cout << "can't initialize app\n";
		return -1;
	}
	app.test_run();

	std::cout << argv[0] << std::endl;
}

