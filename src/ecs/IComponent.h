#pragma once

class IComponent{
public:
    virtual void onStart() = 0;
    virtual void onUpdate() = 0;
    virtual void onDestroy() = 0;
    virtual void reset() = 0;
};
