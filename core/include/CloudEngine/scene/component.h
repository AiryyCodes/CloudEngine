#pragma once

class Node;
struct Component
{
public:
    virtual ~Component() = default;

    virtual void Init() {}
    virtual void Update() {}

    inline Node *GetParent() { return parent; }

public:
    Node *parent;
};
