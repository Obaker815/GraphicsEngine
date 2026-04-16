#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

#include "KeybindManager.h"
#include "Keybind.h"

KeybindManager::KeybindManager()
{ }
KeybindManager::~KeybindManager()
{ }

void KeybindManager::Update(GLFWwindow* window)
{
    for (auto& bind : keybinds)
    {
        int state = glfwGetKey(window, bind->key);

        bind->isDown = (state == GLFW_PRESS);

        if (bind->isDown && !bind->wasDown)
        {
            if (bind->onPress) bind->onPress();
        }
        else if (!bind->isDown && bind->wasDown)
        {
            if (bind->onRelease) bind->onRelease();
        }
        else if (bind->isDown)
        {
            if (bind->active) bind->active();
        }
        if (!bind->isDown)
        {
            if (bind->inactive) bind->inactive();
        }

        bind->wasDown = bind->isDown;
    }
}

void KeybindManager::AddKeybind(Keybind* kb)
{
    keybinds.push_back(kb);
}

void KeybindManager::RemoveKeybind(Keybind* kb)
{
    std::vector<Keybind*>::iterator position = std::find(keybinds.begin(), keybinds.end(), kb);
    if (position != keybinds.end())
        keybinds.erase(position);
}
