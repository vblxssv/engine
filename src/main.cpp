#include "core/Application.h"



int main(int argc, char** argv) {


	Application app(1200, 800);

	if (!app.init()) {
		return -1;
	}
	app.mac_run();
}



