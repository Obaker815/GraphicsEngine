#pragma once
#include <functional>

struct Keybind
{
    // The key value
    int key;

    // Event function pointers
    std::function<void()> onPress   = []() {};
    std::function<void()> onRelease = []() {};
    std::function<void()> active    = []() {};
    std::function<void()> inactive  = []() {};
};
