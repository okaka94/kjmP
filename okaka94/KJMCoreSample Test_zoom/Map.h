#pragma once
#include "Object.h"
class Map :  public Object2D
{
public:
     void Set_position(Vector2D pos);
    void    Set_position(Vector2D pos, Vector2D cam_pos) override;
    void    ScreenToCam(Vector2D cam_pos, Vector2D view_size) override;
    virtual void UpdateVertextBuffer() override;
    bool Frame() override;
};

