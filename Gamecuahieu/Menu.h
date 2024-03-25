#ifndef MENU_H_
#include<iostream>
#include"BaseObject.h"
#include"TextObject.h"
namespace Menu
{
	int ShowGameOver(SDL_Renderer* des, TTF_Font* font);
	int ShowMenu(SDL_Renderer* des, TTF_Font* font);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}
#endif // !MENU_H_
