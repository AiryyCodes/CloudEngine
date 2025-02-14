#pragma once

class IModule
{
public:
    virtual ~IModule() = default;

    virtual void OnInitialize() = 0;
    virtual void OnShutdown() = 0;
};
