﻿#include<iostream>
#include"MainObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time_ = 0;
	sellect_bullet_ = BulletObject::SPHERE_BULLET;
	doublejump = false;
}
MainObject::~MainObject()
{

}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 8;
		height_frame_ = rect_.h;

	}
	return ret;
}
void MainObject::set_clips()
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
		frame_clip_[2].x =2* width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;
		frame_clip_[3].x = 3*width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;
		frame_clip_[4].x = 4*width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;
		frame_clip_[5].x = 5*width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;
		frame_clip_[6].x = 6* width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;
		frame_clip_[7].x = 7*width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

	}
}
void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des);
	
	if (input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if (frame_ >= 8)
	{
		frame_ = 0;
	}
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		SDL_Rect* current_clip = &frame_clip_[frame_];
		SDL_Rect renderQuad = { rect_.x,rect_.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
}
void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if(events.type==SDL_KEYDOWN)
		{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:

			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			UpdateImagePlayer(screen);
			break;
		case SDLK_a:
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
			break;
		case SDLK_l:
			ChangeBullet(sellect_bullet_);
			break;
		case SDLK_w:
			input_type_.up_ = 1;
			break;
		case SDLK_s:
			input_type_.down_ = 1;
			break;
		case SDLK_j:
			input_type_.jump_ = 1;
			break;
		case SDLK_k:
			BulletObject* p_bullet = new BulletObject();
			p_bullet->set_bullet_type(sellect_bullet_);
			p_bullet->LoadImgBullet(screen);
			if (status_ == WALK_LEFT)
			{
				if (input_type_.up_ == 1)
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_UP_LEFT);
					p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
				}
				else if (input_type_.down_ == 1)
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_LEFT);
					p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
				}
				else
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
					p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
				}
			}
			else
			{
				if (input_type_.up_ == 1)
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_UP_RIGHT);
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
				}
				else if (input_type_.down_ == 1)
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_DOWN_RIGHT);
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
				}
				else
				{
					p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
					p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
				}
			}

			p_bullet->set_x_val(20);
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list_.push_back(p_bullet);
			break;
		
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
			input_type_.right_ = 0;

			break;
		case SDLK_a:
			input_type_.left_ = 0;
			break;
		case SDLK_w:
			input_type_.up_ = 0;
		case SDLK_s:
			input_type_.down_ = 0;
		default:
			break;
		}
	}
}
void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
	    }
	}
}
void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += GRAVITY_SPEED;
		if (y_val_ >= MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}
		if (input_type_.left_ == 1)
		{
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += PLAYER_SPEED;
		}
		if (input_type_.jump_ == 1)
		{
			if (on_ground == true)
			{
				y_val_ = -PLAYER_JUMP_VAL;
				on_ground = false;
			}
			else if (on_ground == false && doublejump == true)
			{
				y_val_ = -PLAYER_JUMP_VAL;
				doublejump = false;
			}
			
			input_type_.jump_ = 0;
		}
		CheckToMap(map_data);
		CenterEntityOnmap(map_data);
	}
	if (come_back_time_ > 0)
	{ 
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			on_ground = false;
			if (x_pos_ > 256)
			{
				x_pos_ -=SCREEN_WIDTH/2;// Nua Map
			}
			else
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}
}
void MainObject::CheckToMap(Map& map_data)
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
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = x2 * TILE_SIZE - width_frame_ - 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) // Di chuyển sang trái
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				// Đặt lại vị trí x để tránh va chạm
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
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
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				// Đặt lại vị trí y để tránh va chạm
				y_pos_ = y2 * TILE_SIZE - height_frame_ - 1;
				y_val_ = 0;
				on_ground = true;
				doublejump = true;
				if (status_ == WALK_NONE)
				{
					status_ = WALK_RIGHT;
				}
			}
		}
		else if (y_val_ < 0) // Nhảy lên
		{
			on_ground = false;
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
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
		come_back_time_ = 50;
	}
}
void MainObject::CenterEntityOnmap(Map& map_data) const
{
	// Đặt vị trí bắt đầu của map để nhân vật nằm giữa màn hình
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}
void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground == true)
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//player_left.png", des);
		}
		else
		{
			LoadImg("img//player_right.png", des);
		}
	}
	else
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//jum_left.png", des);
		}
		else
		{
			LoadImg("img//jum_right.png", des);
		}
	}
}
void MainObject::ChangeBullet(const int& sellectbullet)
{
	if (sellect_bullet_ == BulletObject::SPHERE_BULLET)
	{
		sellect_bullet_ = BulletObject::LASER_BULLET;
	}
	else
	{
		sellect_bullet_ = BulletObject::SPHERE_BULLET;
	}
}
