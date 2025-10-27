#include "Keyboard.h"

void Keyboard::update_key(int key, PRESSED_EN state)
{
    if (key >= FIRST_KEY && key <= LAST_KEY) {
        keys[key - FIRST_KEY] = state;
    }
}

PRESSED_EN Keyboard::get_state(int key) const
{
    if (key < FIRST_KEY || key > LAST_KEY) return RELEASED;
    return keys[key - FIRST_KEY];
}

const std::vector<PRESSED_EN>& Keyboard::get_keys() const
{
    return keys;
}

Keyboard::Keyboard() : keys(KEY_COUNT, RELEASED)
{
}


