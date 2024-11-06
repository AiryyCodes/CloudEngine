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

    const int &GetWidth() { return width; }
    void SetWidth(int width);

    const int &GetHeight() { return height; }
    void SetHeight(int height);

    const std::string &GetTitle() { return title; }
    void SetTitle(std::string title);

    GLFWwindow *GetGLFWWindow();

private:
    std::string title;
    int width;
    int height;
};
