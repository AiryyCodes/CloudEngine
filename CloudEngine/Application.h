#pragma once

#include "CloudEngine/Core.h"

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

private:
    Scope<Entry> m_Entry;
};

Application *CreateApplication();