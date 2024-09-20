#pragma once

#include <string>

struct WindowInitProps
{
    std::string title;
    int width;
    int height;
};

class Window
{
public:
    Window(std::string title, int width, int height)
        : title(title), width(width), height(height)
    {
    }

    void Init();
    void Update();
    void Close();
    void Poll();

    bool IsClosing();

private:
    std::string title;
    int width;
    int height;
};
