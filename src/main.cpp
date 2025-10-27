#include "application/Application.h"



int main(int argc, char** argv) {
	Application app(1200, 500, argv[0]);
	if (!app.init()) {
		std::cout << "can't initialize app\n";
		return -1;
	}
	app.test_run2();
}

