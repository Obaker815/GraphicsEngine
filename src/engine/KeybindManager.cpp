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
    for (auto & bind : keybinds)
    {
        if (glfwGetKey(window, bind->key) == GLFW_PRESS)
            bind->onPress();
        else if (glfwGetKey(window, bind->key) == GLFW_RELEASE)
            bind->onRelease();
        else if (glfwGetKey(window, bind->key) == GLFW_REPEAT)
            bind->active();
        else
            bind->inactive();
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
