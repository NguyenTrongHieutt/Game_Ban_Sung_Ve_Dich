#include "BulletObject.h"
#include<iostream>

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ =SPHERE_BULLET;
    flag_bullet = true;
    x_bullet = 0;
    y_bullet = 0;
}


BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if (bullet_type_ == LASER_BULLET)
    {
        ret = LoadImg("img//lazer.png", des);
    }
    else
    {
        ret = LoadImg("img//Circle_bullet.png", des);
    }

    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += (x_val_ );
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= (x_val_);
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP)
    {
        rect_.y -= (y_val_);
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN)
    {
        rect_.y += (y_val_ );
        if (rect_.y >y_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= (x_val_);
        if (rect_.x < 0)
        {
            is_move_ = false;
        }

        rect_.y -= (y_val_ );
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += (x_val_ );
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }

        rect_.y -= (y_val_ );
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_LEFT)
    {
        rect_.x -= (x_val_ );
        if (rect_.x < 0)
        {
            is_move_ = false;
        }

        rect_.y += (y_val_);
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_DOWN_RIGHT)
    {
        rect_.x += (x_val_ );
        if (rect_.x > x_border)
        {
            is_move_ = false;

        }

        rect_.y += (y_val_ );
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}
void BulletObject::HandleMoveThreat(const int& x_border, const int& y_border, const float& x1, const float& y1,const float& x2,const float& y2)
{
    if (flag_bullet == true)
    {
        double angle = atan2(y2 - y1, x2 - x1) * 180 / M_PI;
        double delta_x = cos(angle * M_PI / 180.0) * SPEED_BULLET;
        double delta_y = sin(angle * M_PI / 180.0) * SPEED_BULLET;

            if (x1 >= x2)
            {
                x_bullet = static_cast<int>(delta_x);
                if (y1- HEIGHT_THREAT/2 >= y2)
                {
                    y_bullet = static_cast<int>(delta_y);
                }
                else y_bullet = 0;
                flag_bullet = false;
            }
            else
            {
                x_bullet = static_cast<int>(delta_x);
                if (y1-HEIGHT_THREAT / 2 >= y2)
                {
                    y_bullet = static_cast<int>(delta_y);
                }
                else y_bullet = 0;
                flag_bullet = false;
            }
    }
        rect_.x += x_bullet;
        if (rect_.x < 0 || rect_.x > x_border)
        {
            is_move_ = false;
            flag_bullet = true;
        }

        rect_.y += y_bullet;
        if (rect_.y < 0 || rect_.y > y_border)
        {
            is_move_ = false;
            flag_bullet = true;
        }
}
