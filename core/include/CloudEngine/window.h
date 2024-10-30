#pragma once

#include <string>

struct GLFWwindow;
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

    void SetWidth(int width);
    inline int &GetWidth() { return width; }

    void SetHeight(int height);
    inline int &GetHeight() { return height; }

    GLFWwindow *GetGLFWWindow();

private:
    std::string title;
    int width;
    int height;
};
