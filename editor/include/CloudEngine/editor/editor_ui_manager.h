#pragma once

#include "CloudEngine/editor/editor_window.h"
#include <type_traits>
#include <vector>

class EditorUIManager
{
public:
    EditorUIManager();

    static EditorUIManager &Get();

    template <typename T>
    void RegisterWindow()
    {
        static_assert(std::is_base_of<EditorWindow, T>::value, "T must be dervied from EditorWindow.");

        T *window = new T();
        windows.push_back(window);
    }

    const std::vector<EditorWindow *> &GetWindows() { return windows; }

private:
    std::vector<EditorWindow *> windows;
};

#ifdef EDITOR
#define REGISTER_EDITOR_WINDOW(window) EditorUIManager::Get().RegisterWindow<window>();
#endif
