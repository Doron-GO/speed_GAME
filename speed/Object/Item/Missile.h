#pragma once
#include "ItemBase.h"
class Missile :
    public ItemBase
{
public:

    Missile();
    ~Missile();

    virtual void Update() override;
    virtual void Draw(Vector2DFloat offset)override;
    virtual void Activate(Vector2DFloat playerpos) override;
    virtual bool IsEnd()override;

    void ActivateUpdate();
    void WaitUpdate();
    void IsCollision();

    void ExplosionDraw(Vector2DFloat offset);
    void MissileDraw(Vector2DFloat offset);


private:

    void (Missile::* _update)();
    void (Missile::* _draw)(Vector2DFloat offset);

    Vector2DFloat vel_;
    int missileImg_;
};

