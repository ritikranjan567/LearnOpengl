#include "Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };

void Keyboard::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key < 0 || key > GLFW_KEY_LAST) return;
    keys[key] = action != GLFW_RELEASE;
    keysChanged[key] = action != GLFW_REPEAT;

}

bool Keyboard::key(int key)
{
    return keys[key];
}

bool Keyboard::keyChange(int key)
{
    bool ret = keysChanged[key];
    keysChanged[key] = false;

    return ret;
}

bool Keyboard::keyWentUp(int key)
{
    return !keys[key] && keyChange(key);
}

bool Keyboard::keyWentDown(int key)
{
    return keys[key] && keyChange(key);
}
