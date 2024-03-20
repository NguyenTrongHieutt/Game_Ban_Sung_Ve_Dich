#include "iostream"
#include "PlayerPower.h"


PlayerLives::PlayerLives(void)
{
}


PlayerLives::~PlayerLives(void)
{
}


void PlayerLives::AddPos(const int& xPos)
{
    pos_list_.push_back(xPos);
}

void PlayerLives::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void PlayerLives::Init(SDL_Renderer* screen)
{
    LoadImg("img//player_pw.png", screen);
    number_ = 3;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void PlayerLives::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

void PlayerLives::InCrease()
{
    number_++;
    int last_post = pos_list_.back();
    last_post += 40;
    pos_list_.push_back(last_post);
   
}

//Player Money

PlayerMoney::PlayerMoney()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerMoney::~PlayerMoney()
{

}


void PlayerMoney::Init(SDL_Renderer* screen)
{
    LoadImg("img//money.png", screen);
}


void PlayerMoney::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}