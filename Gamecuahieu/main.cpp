#include <iostream>
#include"CommonFunc.h"
#include"BaseObject.h"
#include"gamemap.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatsObject.h"
#include"ExplosionObject.h"
#include"TextObject.h"
#include"PlayerPower.h"
BaseObject g_background;
TTF_Font* font_time=NULL;



bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window=SDL_CreateWindow("GAME VUI CUA HIEU",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
        if (TTF_Init() == -1)
        {
           success= false;
        }
        font_time = TTF_OpenFont("font//dlxfont.ttf",15);
        if (font_time == NULL)
        {
            success = false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//cityskyline.png", g_screen);
    if (ret == false)
        return false;
    return true;
}
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}
std::vector<ThreatsObject*>MakeThreatsList()
{
    std::vector<ThreatsObject*>list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threats = (dynamic_threats + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImg("img//threat_left.png", g_screen);
            p_threats->set_clips();
            p_threats->set_type_move(ThreatsObject::MOVE_IN_SPACE_TH);
            p_threats->set_x_pos(1000 + i * 800);
            p_threats->set_y_pos(250);
            p_threats->set_input_left(1);
            int pos1 = p_threats->get_x_pos() - 60;
            int pos2 = p_threats->get_x_pos() + 60;
            p_threats->SetAnimationPos(pos1, pos2);
            BulletObject* p_bullet = new BulletObject();
            p_threats->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threats);
        }
    }
    ThreatsObject* threats_objs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threats = (threats_objs + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImg("img//threat_level.png", g_screen);
            p_threats->set_clips();
            p_threats->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threats->set_x_pos(10500+ i*500);
            p_threats->set_y_pos(250);
            p_threats->set_input_left(0);
            BulletObject* p_bullet = new BulletObject();
            p_threats->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threats);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);
    
    MainObject p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();

    PlayerLives player_power;
    player_power.Init(g_screen);
    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH * 0.5 - 300, 8);

    std::vector<ThreatsObject*>threats_list = MakeThreatsList();
    ExplosionObject exp_player;
    bool pRet=exp_player.LoadImg("img//exp3.png", g_screen);
    if (!pRet) return -1;
    exp_player.set_clips();
    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
    if (!tRet) return -1;
    exp_threat.set_clips();

    int num_die = 1;
    //Time text
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
  
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;
    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);
    TextObject numbrave_game;
    numbrave_game.SetColor(TextObject::WHITE_TEXT);
    TextObject notification_brave;
    notification_brave.SetColor(TextObject::WHITE_TEXT);
    bool is_quit = false;
    
    while (!is_quit)
    {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
        
        Map map_data = game_map.getMap();
  
       
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        if (p_player.get_brave() && p_player.GetNumBrave()>0)
        {
                p_player.DoBrave(map_data);
        }
        if (p_player.get_out_area())
        {
            num_die++;
            player_power.Decrease();
            player_power.Render(g_screen);
        }
        if(num_die>3)
        {
            player_power.Decrease();
            player_power.Render(g_screen);
            if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                close();
                SDL_Quit();
                return 0;
            }
        }
        p_player.Show(g_screen);
        p_player.HandleBullet(g_screen,map_data);
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);
        player_power.Show(g_screen);
        player_money.Show(g_screen);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (map_data.start_x_ > p_threat->get_x_pos())
            {
                std::vector<BulletObject*> bullet_LIST = p_threat->get_bullet_list();
                for (int i = 0; i < bullet_LIST.size(); i++)
                {
                    bullet_LIST[i]->set_is_move(false);
                    bullet_LIST[i]->SetRect(p_threat->get_x_pos() - map_data.start_x_, p_threat->get_y_pos());
                }
                continue;
            }
            else if (map_data.start_x_ + SCREEN_WIDTH < p_threat->get_x_pos())
            {
                std::vector<BulletObject*> bullet_LIST = p_threat->get_bullet_list();
                for (int i = 0; i < bullet_LIST.size(); i++)
                {
                    bullet_LIST[i]->set_is_move(false);
                    bullet_LIST[i]->SetRect(p_threat->get_x_pos() - map_data.start_x_, p_threat->get_y_pos());
                }
                break;
            }
            else {
                if (p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen);
                    p_threat->DoPlayer(map_data,g_screen);
                    if (p_threat->get_on_ground())
                    {
                        p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, p_player.get_x_pos(), p_player.get_y_pos(), map_data);
                    }
                    p_threat->Show(g_screen);

                    SDL_Rect rect_player = p_player.GetRectFrame();
                    bool bCol1 = false;
                    if (p_player.get_threat_can_fire() )
                    {
                        std::vector<BulletObject*>tBullet_list = p_threat->get_bullet_list();
                        for (int jj = 0; jj < tBullet_list.size(); jj++)
                        {
                            BulletObject* pt_bullet = tBullet_list.at(jj);
                            if (pt_bullet)
                            {
                                bCol1 = SDLCommonFunc::IsInside(pt_bullet->GetRect(), rect_player);

                            }
                            if (bCol1)
                            {
                                break;
                            }
                        }
                        SDL_Rect rect_threat = p_threat->GetRectFrame();
                        bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                        if (bCol1 == true || bCol2 == true)
                        {
                            int width_exp_frame = exp_player.get_frame_height();
                            int heiht_exp_height = exp_player.get_frame_width();
                            for (int ex = 0; ex < 4; ex++)
                            {
                                int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
                                int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - heiht_exp_height * 0.5;

                                exp_player.set_frame(ex);
                                exp_player.SetRect(x_pos, y_pos);
                                exp_player.Show(g_screen);
                                SDL_RenderPresent(g_screen);
                            }
                            num_die++;
                            if (num_die <= 3)
                            {
                                p_player.SetRect(0, 0);
                                p_player.set_comebeack_time(60);
                                SDL_Delay(500);
                                player_power.Decrease();
                                player_power.Render(g_screen);
                                continue;
                            }
                            else
                            {
                                player_power.Decrease();
                                player_power.Render(g_screen);
                                if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                                {
                                    p_threat->Free();
                                    close();
                                    SDL_Quit();
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_heigh = exp_threat.get_frame_height();

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r= 0; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if (map_data.start_x_ > obj_threat->get_x_pos())continue;
                    else if (map_data.start_x_ + SCREEN_WIDTH < obj_threat->get_x_pos())
                    {
                        break;
                    }
                    else {
                        if (obj_threat != NULL)
                        {
                            SDL_Rect tRect;
                            tRect.x = obj_threat->GetRect().x;
                            tRect.y = obj_threat->GetRect().y;
                            tRect.w = obj_threat->get_width_frame();
                            tRect.h = obj_threat->get_height_frame();
                            SDL_Rect bRect = p_bullet->GetRect();
                            bool bCol = SDLCommonFunc::IsInside(bRect, tRect);
                            if (bCol)
                            {
                                if (p_bullet->get_bullet_type() == BulletObject::SPHERE_BULLET &&
                                    obj_threat->get_typemove() == ThreatsObject::MOVE_IN_SPACE_TH)
                                {
                                    mark_value += 100;
                                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                                    {
                                        int x_pos = obj_threat->GetRect().x - frame_exp_width * 0.5;
                                        int y_pos = obj_threat->GetRect().y - frame_exp_heigh * 0.5;
                                        exp_threat.set_frame(ex);
                                        exp_threat.SetRect(x_pos, y_pos);
                                        exp_threat.Show(g_screen);
                                    }
                                    obj_threat->Free();
                                    threats_list.erase(threats_list.begin() + t);
                                }
                                else if(p_bullet->get_bullet_type() == BulletObject::LASER_BULLET &&
                                    obj_threat->get_typemove() == ThreatsObject::STATIC_THREAT)
                                {
                                    mark_value += 200;
                                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                                    {
                                        int x_pos = obj_threat->GetRect().x - frame_exp_width * 0.5;
                                        int y_pos = obj_threat->GetRect().y - frame_exp_heigh * 0.5;
                                        exp_threat.set_frame(ex);
                                        exp_threat.SetRect(x_pos, y_pos);
                                        exp_threat.Show(g_screen);
                                    }
                                    obj_threat->Free();
                                    threats_list.erase(threats_list.begin() + t);
                                }
                                p_player.RemoveBullet(r);
                            }
                        }
                    }
                }
            }
        }
        //Show game time
        std::string str_time = "TIME: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        Uint32 minutes = val_time / 60; // Số phút
        Uint32 seconds = val_time % 60; // Số giây còn lại

        if (val_time <= 0)
        {
            if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else
        {
            std::string str_min = std::to_string(minutes);
            std::string str_sec = std::to_string(seconds);
            if (seconds < 10) {
                str_sec = "0" + str_sec;
            }

            str_time += str_min + ":" + str_sec;
            time_game.SetText(str_time);
            time_game.loadFromRenderedText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
        }
        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.loadFromRenderedText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

        int num_brave = p_player.GetNumBrave();
        std::string numbrave_str = std::to_string(num_brave);
        numbrave_game.SetText(numbrave_str);
        numbrave_game.loadFromRenderedText(font_time, g_screen);
        numbrave_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 + 250, 15);

        int money_val = p_player.GetMoneyCount();
        std::string money_str = std::to_string(money_val);
        money_game.SetText(money_str);
        money_game.loadFromRenderedText(font_time, g_screen);
        money_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

        if (num_brave== 0)
        {
            std::string notification = "NO BRAVE";
            notification_brave.SetText(notification);
            notification_brave.loadFromRenderedText(font_time, g_screen);
            notification_brave.RenderText(g_screen, SCREEN_WIDTH * 0.5 + 270, 15);
        }
        SDL_RenderPresent(g_screen);
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threats = threats_list.at(i);
        if (p_threats)
        {
            p_threats->Free();
            p_threats = NULL;
        }
    }
    threats_list.clear();
    close();
    return 0;
}
