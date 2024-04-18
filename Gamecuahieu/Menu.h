#ifndef MENU_H_
#include<iostream>
#include"BaseObject.h"
#include"TextObject.h"
#include"ImpTimer.h"
namespace Menu
{
	int ShowVitory(SDL_Renderer* des, TTF_Font* font,Mix_Chunk* sound,bool& onaudio);
	int ShowGameOver(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool& onaudio);
	int ShowPause(SDL_Renderer* des, TTF_Font* font,ImpTimer* time, Mix_Chunk* sound, bool& onaudio);
	int ShowMenu(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool& onaudio);
	int ShowMenuNoCon(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool& onaudio);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}
#endif // !MENU_H_
