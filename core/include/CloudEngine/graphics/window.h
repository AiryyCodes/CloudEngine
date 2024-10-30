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

    inline int &GetWidth() { return width; }
    void SetWidth(int width);

    inline int &GetHeight() { return height; }
    void SetHeight(int height);

    inline std::string GetTitle() { return title; }
    void SetTitle(std::string title);

    GLFWwindow *GetGLFWWindow();

private:
    std::string title;
    int width;
    int height;
};
