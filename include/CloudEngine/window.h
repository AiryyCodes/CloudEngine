#pragma once

#include <string>

class Window
{
public:
    Window(std::string title, int width, int height)
        : title(title), width(width), height(height)
    {
    }

    void Init();
    void Update();
    void Poll();

    bool IsClosing();

private:
    std::string title;
    int width;
    int height;
};
