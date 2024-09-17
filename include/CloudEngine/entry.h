#pragma once

class CEEntry
{
public:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
};

CEEntry *CEInit();
