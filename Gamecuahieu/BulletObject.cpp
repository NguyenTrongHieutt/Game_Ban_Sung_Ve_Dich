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

void BulletObject::HandleMove(const int& x_border, const int& y_border,Map& map_data)
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
        rect_.x -= x_val_;
        if (rect_.x < 0)
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
    CheckToMapMain( map_data);
    
}
void BulletObject:: CheckToMapMain(Map& map_data)
{
    
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min =rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;
    int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;

    // Xử lý va chạm theo chiều ngang
    x1 = (int)(map_data.start_x_+rect_.x + x_val_) / TILE_SIZE;
    x2 = (int)(map_data.start_x_ + rect_.x + x_val_ + rect_.w - 1) / TILE_SIZE;

    y1 = (int)(rect_.y) / TILE_SIZE;
    y2 = (int)(rect_.y + height_min - 1) / TILE_SIZE;

    // Kiểm tra va chạm với tile theo chiều ngang
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // Di chuyển sang phải
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            
           
                if ((val1 != BLANK_TILE && val1 != STATE_MONEY&&val1!=ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY&&val2!=ITEM_BRAVE))
                {
                    is_move_ = false;
                }
            
        }
        else if (x_val_ < 0) // Di chuyển sang trái
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
          
            
            
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
                {
                    is_move_ = false;
                }
            
        }
    }

    // Xử lý va chạm theo chiều dọc
    x1 = (int)(map_data.start_x_ + rect_.x) / TILE_SIZE;
    x2 = (int)(map_data.start_x_ + rect_.x + width_min) / TILE_SIZE;

    y1 = (int)(rect_.y + y_val_) / TILE_SIZE;
    y2 = (int)(rect_.y + y_val_ + rect_.h - 1) / TILE_SIZE;

    // Kiểm tra va chạm với tile theo chiều dọc
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0) // Rơi xuống
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
           
            
            
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
                {
                    is_move_ = false;
                }
            
        }
        else if (y_val_ < 0) // Nhảy lên
        {
        
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
           
            
            
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
                {
                    is_move_=false;
                }
            
        }
    }

}
void BulletObject::HandleMoveThreat(const int& x_border, const int& y_border, const float& x1, const float& y1,const float& x2,const float& y2,Map& map_data)
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
        CheckToMapThreat(map_data);
}
void BulletObject::HandleMoveBoss(const int& x_border, const int& y_border, const float& x1, const float& y1, const float& x2, const float& y2, Map& map_data)
{
    if (flag_bullet == true)
    {
        double angle = atan2(y2 - y1, x2 - x1) * 180 / M_PI;
        double delta_x = cos(angle * M_PI / 180.0) * SPEED_BOSS;
        double delta_y = sin(angle * M_PI / 180.0) * SPEED_BOSS;

        if (x1 >= x2)
        {
            x_bullet = static_cast<int>(delta_x);
            if (y1 - HEIGHT_THREAT / 2 >= y2)
            {
                y_bullet = static_cast<int>(delta_y);
            }
            else y_bullet = 0;
            flag_bullet = false;
        }
        else
        {
            x_bullet = static_cast<int>(delta_x);
            if (y1 - HEIGHT_THREAT / 2 >= y2)
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
    CheckToMapThreat(map_data);
}
void BulletObject::CheckToMapThreat(Map& map_data)
{
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;
    int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;

    // Xử lý va chạm theo chiều ngang
    x1 = (int)(map_data.start_x_ + rect_.x + x_bullet) / TILE_SIZE;
    x2 = (int)(map_data.start_x_ + rect_.x + x_bullet + rect_.w - 1) / TILE_SIZE;

    y1 = (int)(rect_.y) / TILE_SIZE;
    y2 = (int)(rect_.y + height_min - 1) / TILE_SIZE;

    // Kiểm tra va chạm với tile theo chiều ngang
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_bullet > 0) // Di chuyển sang phải
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];


            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
            {
                is_move_ = false;
                flag_bullet = true;
            }

        }
        else if (x_bullet < 0) // Di chuyển sang trái
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];



            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
            {
                is_move_ = false;
                flag_bullet = true;
            }

        }
    }

    // Xử lý va chạm theo chiều dọc
    x1 = (int)(map_data.start_x_ + rect_.x) / TILE_SIZE;
    x2 = (int)(map_data.start_x_ + rect_.x + width_min) / TILE_SIZE;

    y1 = (int)(rect_.y + y_bullet) / TILE_SIZE;
    y2 = (int)(rect_.y + y_bullet + rect_.h - 1) / TILE_SIZE;

    // Kiểm tra va chạm với tile theo chiều dọc
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_bullet > 0) // Rơi xuống
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];



            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
            {
                is_move_ = false;
                flag_bullet = true;
            }

        }
        else if (y_bullet < 0) // Nhảy lên
        {

            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];



            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
            {
                is_move_ = false;
                flag_bullet = true;
            }

        }
    }
}