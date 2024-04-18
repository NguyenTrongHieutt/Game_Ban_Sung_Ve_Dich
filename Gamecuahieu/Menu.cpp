#include<iostream>
#include"Menu.h"
int Menu::ShowMenu(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool &onaudio)
{
    BaseObject g_img_menu;
    bool ret = g_img_menu.LoadImg("img//background_menu_hascon.png", des);
    if (ret == false)
    {
        return 2;
    }
    SDL_SetRenderDrawColor(des, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(des);
    g_img_menu.Render(des, NULL);
	const int kMenuItemNum = 3;
	TextObject text_menu[kMenuItemNum];

    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 450;
    pos_arr[2].x = 200;
    pos_arr[2].y = 500;
	text_menu[0].SetText("PLAY GAME");
	text_menu[0].SetColor(TextObject::WHITE_TEXT);
	
	text_menu[1].SetText("CONTINUE");
	text_menu[1].SetColor(TextObject::WHITE_TEXT);

    text_menu[2].SetText("EXIT");
    text_menu[2].SetColor(TextObject::WHITE_TEXT);
	bool selected[kMenuItemNum] = { 0, 0,0};
	int xm = 0;
	int ym = 0;
	SDL_Event m_event;
	while (true)
	{
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym,rect))
                    {
                        g_img_menu.Free();
                        Mix_PlayChannel(CHANNEL_EVENT, sound, 0);
                        return i;                       
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_event.key.keysym.sym == SDLK_u)
                {
                    if (onaudio)
                    {
                        Mix_Volume(-1, 0);       // Tắt tất cả các channel
                        Mix_VolumeMusic(0);      // Tắt music
                        onaudio = false;
                    }
                    else if (!onaudio)
                    {
                        Mix_Volume(-1, 100);       // Bật tất cả các channel
                        Mix_VolumeMusic(100);      // Bật music
                        onaudio = true;
                    }

                }
                break;
            }
            }
        }
        text_menu[0].loadFromRenderedText(font, des);
        text_menu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);
        text_menu[1].loadFromRenderedText(font, des);
        text_menu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);
        text_menu[2].loadFromRenderedText(font, des);
        text_menu[2].RenderText(des, pos_arr[2].x, pos_arr[2].y);

        SDL_RenderPresent(des);
    }
   
    return 1;
}
int Menu::ShowMenuNoCon(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool& onaudio)
{
    BaseObject g_img_menu;
    bool ret = g_img_menu.LoadImg("img//background_menu.png", des);
    if (ret == false)
    {
        return 1;
    }
    SDL_SetRenderDrawColor(des, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(des);
    g_img_menu.Render(des, NULL);
    const int kMenuItemNum = 3;
    TextObject text_menu[kMenuItemNum];

    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 450;
    text_menu[0].SetText("PLAY GAME");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);

    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);
    bool selected[kMenuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        g_img_menu.Free();
                        Mix_PlayChannel(CHANNEL_EVENT, sound, 0);
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_event.key.keysym.sym == SDLK_u)
                {
                    if (onaudio)
                    {
                        Mix_Volume(-1, 0);       // Tắt tất cả các channel
                        Mix_VolumeMusic(0);      // Tắt music
                        onaudio = false;
                    }
                    else if (!onaudio)
                    {
                        Mix_Volume(-1, 100);       // Bật tất cả các channel
                        Mix_VolumeMusic(100);      // Bật music
                        onaudio = true;
                    }

                }
                break;
            }
            }
        }
        text_menu[0].loadFromRenderedText(font, des);
        text_menu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);
        text_menu[1].loadFromRenderedText(font, des);
        text_menu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);

        SDL_RenderPresent(des);
    }

    return 1;
}
int Menu::ShowPause(SDL_Renderer* des, TTF_Font* font,ImpTimer* time, Mix_Chunk* sound, bool& onaudio)
{
    BaseObject g_img_menu;
    bool ret = g_img_menu.LoadImg("img//background_continue.png", des);
    if (ret == false)
    {
        return 2;
    }
    SDL_SetRenderDrawColor(des, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(des);
    g_img_menu.Render(des, NULL);
    const int kMenuItemNum = 3;
    TextObject text_menu[kMenuItemNum];

    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 450;
    pos_arr[2].x = 200;
    pos_arr[2].y = 500;
    text_menu[0].SetText("CONTINUE");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);

    text_menu[1].SetText("BACK TO MENU");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);

    text_menu[2].SetText("EXIT");
    text_menu[2].SetColor(TextObject::WHITE_TEXT);
    bool selected[kMenuItemNum] = { 0, 0,0 };
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        while (SDL_PollEvent(&m_event))
        {
            time->paused();
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        g_img_menu.Free();
                        Mix_PlayChannel(CHANNEL_EVENT, sound, 0);
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_event.key.keysym.sym == SDLK_u)
                {
                    if (onaudio)
                    {
                        Mix_Volume(-1, 0);       // Tắt tất cả các channel
                        Mix_VolumeMusic(0);      // Tắt music
                        onaudio = false;
                    }
                    else if (!onaudio)
                    {
                        Mix_Volume(-1, 100);       // Bật tất cả các channel
                        Mix_VolumeMusic(100);      // Bật music
                        onaudio = true;
                    }

                }
                break;
            }
            }
        }
        text_menu[0].loadFromRenderedText(font, des);
        text_menu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);
        text_menu[1].loadFromRenderedText(font, des);
        text_menu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);
        text_menu[2].loadFromRenderedText(font, des);
        text_menu[2].RenderText(des, pos_arr[2].x, pos_arr[2].y);

        SDL_RenderPresent(des);
    }

    return 1;
}
int Menu::ShowVitory(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* sound, bool& onaudio)
{
    BaseObject vicotry;
    bool ret = vicotry.LoadImg("img//BackgroundVTR.png", des);
    if (ret == false)
    {
        return 1;
    }
    SDL_SetRenderDrawColor(des, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(des);
    vicotry.Render(des, NULL);
    const int kMenuItemNum = 2;
    TextObject text_menu[kMenuItemNum];

    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 450;
    text_menu[0].SetText("BACK TO MENU");
    text_menu[0].SetColor(TextObject::WHITE_TEXT);


    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject::WHITE_TEXT);

    bool selected[kMenuItemNum] = { 0, 0 };
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
            {
                xm = m_event.motion.x;
                ym = m_event.motion.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(TextObject::WHITE_TEXT);
                        }
                    }
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m_event.button.x;
                ym = m_event.button.y;

                for (int i = 0; i < kMenuItemNum; i++)
                {
                    SDL_Rect rect;
                    rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                    rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                    if (CheckFocusWithRect(xm, ym, rect))
                    {
                        vicotry.Free();
                        Mix_PlayChannel(CHANNEL_EVENT, sound, 0);
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m_event.key.keysym.sym == SDLK_u)
                {
                    if (onaudio)
                    {
                        Mix_Volume(-1, 0);       // Tắt tất cả các channel
                        Mix_VolumeMusic(0);      // Tắt music
                        onaudio = false;
                    }
                    else if (!onaudio)
                    {
                        Mix_Volume(-1, 100);       // Bật tất cả các channel
                        Mix_VolumeMusic(100);      // Bật music
                        onaudio = true;
                    }

                }
                break;
            }
            }
        }
        text_menu[0].loadFromRenderedText(font, des);
        text_menu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);
        text_menu[1].loadFromRenderedText(font, des);
        text_menu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);

        SDL_RenderPresent(des);
    }
}
    int Menu::ShowGameOver(SDL_Renderer * des, TTF_Font * font, Mix_Chunk* sound, bool& onaudio)
    {
        BaseObject game_over;
        bool ret = game_over.LoadImg("img//BackgroundGOV.png", des);
        if (ret == false)
        {
            return 1;
        }
        SDL_SetRenderDrawColor(des, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(des);
        game_over.Render(des, NULL);
        const int kMenuItemNum = 2;
        TextObject text_menu[kMenuItemNum];

        SDL_Rect pos_arr[kMenuItemNum];
        pos_arr[0].x = 200;
        pos_arr[0].y = 400;

        pos_arr[1].x = 200;
        pos_arr[1].y = 450;
        text_menu[0].SetText("BACK TO MENU");
        text_menu[0].SetColor(TextObject::WHITE_TEXT);


        text_menu[1].SetText("EXIT");
        text_menu[1].SetColor(TextObject::WHITE_TEXT);

        bool selected[kMenuItemNum] = { 0, 0 };
        int xm = 0;
        int ym = 0;
        SDL_Event m_event;
        while (true)
        {
            while (SDL_PollEvent(&m_event))
            {
                switch (m_event.type)
                {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        SDL_Rect rect;
                        rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                        rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                        if (CheckFocusWithRect(xm, ym, rect))
                        {
                            if (selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                            }
                        }
                        else
                        {
                            if (selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].SetColor(TextObject::WHITE_TEXT);
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for (int i = 0; i < kMenuItemNum; i++)
                    {
                        SDL_Rect rect;
                        rect.x = pos_arr[i].x; rect.y = pos_arr[i].y;
                        rect.w = text_menu[i].getWidth(); rect.h = text_menu[i].getHeight();
                        if (CheckFocusWithRect(xm, ym, rect))
                        {
                            game_over.Free();
                            Mix_PlayChannel(CHANNEL_EVENT, sound, 0);
                            return i;
                        }
                    }
                }
                break;
                case SDL_KEYDOWN:
                {
                    if (m_event.key.keysym.sym == SDLK_u)
                    {
                        if (onaudio)
                        {
                            Mix_Volume(-1, 0);       // Tắt tất cả các channel
                            Mix_VolumeMusic(0);      // Tắt music
                            onaudio = false;
                        }
                        else if (!onaudio)
                        {
                            Mix_Volume(-1, 100);       // Bật tất cả các channel
                            Mix_VolumeMusic(100);      // Bật music
                            onaudio = true;
                        }

                    }
                    break;
                }
                }
            }
            text_menu[0].loadFromRenderedText(font, des);
            text_menu[0].RenderText(des, pos_arr[0].x, pos_arr[0].y);
            text_menu[1].loadFromRenderedText(font, des);
            text_menu[1].RenderText(des, pos_arr[1].x, pos_arr[1].y);

            SDL_RenderPresent(des);
        }

        return 1;
    }

    bool Menu::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
    {
        if (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h)
        {
            return true;
        }
        return false;
    }