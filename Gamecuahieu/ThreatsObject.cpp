#include<iostream>
#include "ThreatsObject.h"



ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	come_back_time_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	on_ground = 0;
	think_time_ = 0;
	frame_ = 0;
	type_move_ = STATIC_THREAT;
	input_type_.left_ = 0;
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 0;
}
ThreatsObject::~ThreatsObject()
{

}
bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / THREATS_NUM_FRAME;
		height_frame_ = rect_.h;
	}

	return ret;
}
bool ThreatsObject::LoadImg2(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w;
		height_frame_ = rect_.h;
	}

	return ret;
}
SDL_Rect ThreatsObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;
	return rect;
}
void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = width_frame_ * 2;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = width_frame_ * 3;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = width_frame_ * 4;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = width_frame_ * 5;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = width_frame_ * 6;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = width_frame_ * 7;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;
	}
}
void ThreatsObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 8)
		{
			frame_ = 0;
		}
		SDL_Rect* current_clip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}
void ThreatsObject::Show2(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		
		SDL_Rect frame_clip = { 0,0,width_frame_,height_frame_ };
		SDL_Rect* current_clip = &frame_clip;
		
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}
void ThreatsObject::DoPlayer(Map& gMap, SDL_Renderer* screen)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREATS_GRAVITY_SPEED;
		if (y_val_ >= THREATS_MAX_FALL_SPEED)
		{
			y_val_ = THREATS_MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;
		}

		else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED;
		}
		CheckToMap(gMap,screen);
	}
	else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreats();
		}
	}
}
void ThreatsObject:: DoPlayer2(Map& gMap, SDL_Renderer* screen)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREATS_GRAVITY_SPEED;
		if (y_val_ >= THREATS_MAX_FALL_SPEED)
		{
			y_val_ = THREATS_MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= TRAP_SPEED;
		}

		else if (input_type_.right_ == 1)
		{
			x_val_ += TRAP_SPEED;
		}
		CheckToMap2(gMap, screen);
	}
	else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreats();
		}
	}
}
void ThreatsObject::DoPlayer3(Map& gMap, SDL_Renderer* screen)
{
	x_val_ = 0;
	if (input_type_.up_ == 1)
	{
		y_val_ -= THREAT2_SPEED;
	}

	else if (input_type_.down_== 1)
	{
		y_val_ += THREAT2_SPEED;
	}
	CheckToMap3(gMap, screen);
}
void ThreatsObject::InitThreats()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256;//Back 4 tile
		animation_a_ -= 256;
		animation_b_ -= 256;
	}
	else
	{
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}
void ThreatsObject::RemoveBullet(const int& idx)
{
	int size = bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
void ThreatsObject::CheckToMap(Map& map_data,SDL_Renderer* screen)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	// Xử lý va chạm theo chiều ngang
	x1 = (int)(x_pos_ + x_val_) / TILE_SIZE;
	x2 = (int)(x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (int)(y_pos_) / TILE_SIZE;
	y2 = (int)(y_pos_ + height_min - 1) / TILE_SIZE;

	// Kiểm tra va chạm với tile theo chiều ngang
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // Di chuyển sang phải
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1!=ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2!=ITEM_BRAVE))
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = x2 * TILE_SIZE - width_frame_ - 1;
				x_val_ = -x_val_; // Đổi hướng di chuyển
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//threat_left.png", screen);

				
			}
		}
		else if (x_val_ < 0) // Di chuyển sang trái
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = -x_val_; // Đổi hướng di chuyển
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				LoadImg("img//threat_right.png", screen);
				
			}
		}
	}

	// Xử lý va chạm theo chiều dọc
	x1 = (int)(x_pos_) / TILE_SIZE;
	x2 = (int)(x_pos_ + width_min) / TILE_SIZE;

	y1 = (int)(y_pos_ + y_val_) / TILE_SIZE;
	y2 = (int)(y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	// Kiểm tra va chạm với tile theo chiều dọc
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0) // Rơi xuống
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
				{
					// Đặt lại vị trí y để tránh va chạm
					y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
					y_val_ = 0;
					on_ground = true;
					
				}
			
		}
		else if (y_val_ < 0) // Nhảy lên
		{
			on_ground = false;
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
				{
					// Đặt lại vị trí y để tránh va chạm
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			
		}
	}

	// Cập nhật vị trí mới của nhân vật
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
	if (y_pos_ > map_data.max_y_)
	{
		on_ground = false;
		come_back_time_ = 50;
	}
}
void ThreatsObject::CheckToMap2(Map& map_data, SDL_Renderer* screen)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	// Xử lý va chạm theo chiều ngang
	x1 = (int)(x_pos_ + x_val_) / TILE_SIZE;
	x2 = (int)(x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (int)(y_pos_) / TILE_SIZE;
	y2 = (int)(y_pos_ + height_min - 1) / TILE_SIZE;

	// Kiểm tra va chạm với tile theo chiều ngang
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // Di chuyển sang phải
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = x2 * TILE_SIZE - width_frame_ - 1;
				x_val_ = -x_val_; // Đổi hướng di chuyển
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				


			}
		}
		else if (x_val_ < 0) // Di chuyển sang trái
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = -x_val_; // Đổi hướng di chuyển
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				

			}
		}
	}

	// Xử lý va chạm theo chiều dọc
	x1 = (int)(x_pos_) / TILE_SIZE;
	x2 = (int)(x_pos_ + width_min) / TILE_SIZE;

	y1 = (int)(y_pos_ + y_val_) / TILE_SIZE;
	y2 = (int)(y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	// Kiểm tra va chạm với tile theo chiều dọc
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0) // Rơi xuống
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí y để tránh va chạm
				y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
				y_val_ = 0;
				on_ground = true;

			}

		}
		else if (y_val_ < 0) // Nhảy lên
		{
			on_ground = false;
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí y để tránh va chạm
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}

		}
	}

	// Cập nhật vị trí mới của nhân vật
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
	if (y_pos_ > map_data.max_y_)
	{
		on_ground = false;
		come_back_time_ = 50;
	}
}
void ThreatsObject::CheckToMap3(Map& map_data, SDL_Renderer* screen)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	// Xử lý va chạm theo chiều dọc
	x1 = (int)(x_pos_) / TILE_SIZE;
	x2 = (int)(x_pos_ + width_min) / TILE_SIZE;

	y1 = (int)(y_pos_ + y_val_) / TILE_SIZE;
	y2 = (int)(y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	// Kiểm tra va chạm với tile theo chiều dọc
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0) // Rơi xuống
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí y để tránh va chạm
				y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
				y_val_ = 0;
				input_type_.down_ = 0;
				input_type_.up_ = 1;

			}

		}
		else if (y_val_ < 0) // Nhảy lên
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != ITEM_BRAVE) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != ITEM_BRAVE))
			{
				// Đặt lại vị trí y để tránh va chạm
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
				input_type_.down_ = 1;
				input_type_.up_ = 0;
			}

		}
	}

	// Cập nhật vị trí mới của nhân vật
	x_pos_ += x_val_;
	y_pos_ += y_val_;
	if (y_pos_+height_frame_ >= map_data.max_y_)
	{
		input_type_.down_ = 0;
		input_type_.up_ = 1;
	}
	else if (y_pos_ <= 0)
	{
		input_type_.down_ = 1;
		input_type_.up_ = 0;
	}
}
void ThreatsObject::ImpMoveType(SDL_Renderer* screen,const float& x,const float& y)
{
	if (type_move_ == STATIC_THREAT)
	{
		if(x_pos_>=x) LoadImg("img//threat_level.png", screen);
		else LoadImg("img//threat_level_right.png", screen);
	}
	else
	{
		if (on_ground == true)
		{
			if (x_pos_ > animation_b_)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("img//threat_left.png", screen);
			}
			else if (x_pos_ < animation_a_)
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				LoadImg("img//threat_right.png", screen);
			}
		}
		else
		{
			if (input_type_.left_ == 1)
			{
				LoadImg("img//threat_left.png", screen);
			}
		}
	}
}
void ThreatsObject::ImpMoveType2(SDL_Renderer* screen, const float& x, const float& y)
{
	if (type_move_ == STATIC_THREAT)
	{
		LoadImg2("img//Gaithang.png", screen);
	}
	else
	{
		if (on_ground == true)
		{
			if (x >= animation_a_ && x <= animation_b_ && x_pos_ >= x)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg2("img//trap.png", screen);
			}
			else if (x>= animation_a_&&x<= animation_b_&& x_pos_<=x)
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				LoadImg2("img//trap.png", screen);
			}
			else
			{
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				LoadImg2("img//trap.png", screen);
			}
		}
		else
		{
			input_type_.right_ = 0;
			input_type_.left_ = 0;
			LoadImg2("img//trap.png", screen);
		}
	}
}
void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet!=NULL)
	{
		p_bullet->set_bullet_type(BulletObject::SPHERE_BULLET);
		bool ret= p_bullet-> LoadImgBullet(screen);
		if (ret)
		{
			p_bullet->set_is_move(false);			
			bullet_list_.push_back(p_bullet);
		}
	}
}
void ThreatsObject::InitBulletTrap(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
		bool ret = p_bullet->LoadImgBullet(screen);
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->SetRect(rect_.x, rect_.y);
			bullet_list_.push_back(p_bullet);
		}
	}
}
void ThreatsObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit, const float& x2,const float& y2,Map& map_data)
{

		for (int i = 0; i < bullet_list_.size(); i++)
		{
			BulletObject* p_bullet = bullet_list_.at(i);
			if (p_bullet != NULL)
			{

				if (p_bullet->get_is_move() == true)
				{

					p_bullet->HandleMoveThreat(x_limit, y_limit, x_pos_, y_pos_, x2, y2, map_data);
					p_bullet->Render(des);
				}
				else
				{
					p_bullet->set_is_move(true);
					p_bullet->SetRect(rect_.x, rect_.y);
				}

			}
		}
	
}
void ThreatsObject::MakeBulletTrap(SDL_Renderer* des, const int& x_limit, const int& y_limit, const float& x2, const float& y2, Map& map_data)
{

	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL)
		{

			if (p_bullet->get_is_move() == true)
			{
				if (x2 >= x_pos_ - 128 && x2 <= x_pos_ + 128)
				{
					p_bullet->HandleMoveTrap(x_limit, y_limit, x_pos_, y_pos_, x2, y2, map_data);
					p_bullet->Render(des);
				}
				else
				{
					bullet_list_.erase(bullet_list_.begin() + i);
					if (p_bullet != NULL)
					{
						delete p_bullet;
						p_bullet = NULL;
					}
				}
			}
			else
			{
				bullet_list_.erase(bullet_list_.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}

		}
	}

}