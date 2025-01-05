#pragma once

#include "CloudEngine/Core.h"
#include "CloudEngine/Window/Window.h"

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

    static Application &Get();

private:
    Scope<Entry> m_Entry;
    Ref<Window> m_MainWindow;
};

Application *CreateApplication();