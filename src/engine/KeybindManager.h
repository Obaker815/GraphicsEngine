#pragma once

#include "Keybind.h"
#include <vector>

class KeybindManager
{
public:
    KeybindManager();
    ~KeybindManager();

    void Update(GLFWwindow* window);
    void AddKeybind(Keybind* kb);
    void RemoveKeybind(Keybind* kb);

private:
    std::vector<Keybind*> keybinds;
};
