#include "core/Application.h"

int main() {
    try {
        Application app(AppConfig::from_file("res/config.ini"));
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return -1;
    }
}
