#include"CommonFunc.h"
#include<iostream>

bool SDLCommonFunc::CheckCollision(const  SDL_Rect& object1, const SDL_Rect& object2)
{
    int x1 = object1.x;
    int w1 = object1.w;
    int y1 = object1.y;
    int h1 = object1.h;

    
    int x2 = object2.x;
    int w2 = object2.w;
    int y2 = object2.y;
    int h2 = object2.h;

    if ((x1 + w1 >= x2) && (x2 + w2 >= x1) && (y1 + h1 >= y2) && (y2 + h2 >= y1)) {
        return true; 
    }

    return false; 
}
bool SDLCommonFunc::IsInside(const SDL_Rect& rectA, const SDL_Rect& rectB) {
   
    int leftA = rectA.x;
    int rightA = rectA.x + rectA.w;
    int topA = rectA.y;
    int bottomA = rectA.y + rectA.h;

    
    int leftB = rectB.x;
    int rightB = rectB.x + rectB.w;
    int topB = rectB.y;
    int bottomB = rectB.y + rectB.h;

   
    return leftA >= leftB && rightA <= rightB && topA >= topB && bottomA <= bottomB;
}

