#pragma once

#include "Engine/Core.h"
#include "Engine/Window/Window.h"

class Entry
{
public:
    virtual ~Entry() = default;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() {}
};

class Application
{
public:
    Application();

    void Init();
    void Update();
    void Render();

    template <typename T>
    void SetEntry()
    {
        m_Entry = CreateScope<T>();
    }

    const Scope<Entry> &GetEntry() { return m_Entry; }
    const Ref<Window> &GetMainWindow() { return m_MainWindow; }

    bool IsInitialized() { return m_Initialized; }

    static Application &Get();

private:
    Scope<Entry> m_Entry;
    Ref<Window> m_MainWindow;

    bool m_Initialized = false;
};

Application *CreateApplication();
