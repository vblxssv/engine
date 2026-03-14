#pragma once
#include <vector>


enum PRESSED_EN {
	RELEASED,
	PRESSED
};

class Keyboard {
private:
	const int FIRST_KEY = 32;
	const int LAST_KEY = 348;
	const int KEY_COUNT = LAST_KEY - FIRST_KEY + 1;
	std::vector<PRESSED_EN> keys;

public:
	Keyboard();

	void update_key(int key, PRESSED_EN state);

	PRESSED_EN get_state(int key) const;

	const std::vector<PRESSED_EN>& get_keys() const;
};



