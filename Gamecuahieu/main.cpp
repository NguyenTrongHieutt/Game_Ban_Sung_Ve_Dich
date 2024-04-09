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
#include"Geometric.h"
#include"BossObject.h"
#include"Menu.h"
#include"Game.h"
#include"BossMini.h"
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
}
std::vector<ThreatsObject*>MakeThreatsList()
{
    std::vector<ThreatsObject*>list_threats;
    ThreatsObject* dynamic_threats = new ThreatsObject[30];
    for (int i = 0; i < 30; i++)
    {
        ThreatsObject* p_threats = (dynamic_threats + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImg("img//threat_left.png", g_screen);
            p_threats->set_clips();
            p_threats->set_type_move(ThreatsObject::MOVE_IN_SPACE_TH);
            p_threats->set_x_pos(1000 + i * SCREEN_WIDTH/2);
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
    ThreatsObject* threats_objs = new ThreatsObject[30];
    for (int i = 0; i < 30; i++)
    {
        ThreatsObject* p_threats = (threats_objs + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImg("img//threat_level.png", g_screen);
            p_threats->set_clips();
            p_threats->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threats->set_x_pos(10900+ i*700);
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
    bool Playgame = true;
    while (Playgame)
    {
        bool Continue = false;

        if (InitData() == false)
            return -1;

        //Boss Threat
        BossObject bossObject;
        int num_boss = 15;
        bool creat_threat = true;
        MainObject p_player;
        int num_die = 3;
        bool showboss = false;
        ImpTimer fps_timer;
        Uint32 timegame = 300;
        Uint32 val_time = 300;
        GameMap game_map;
        std::ifstream File("HaveContinue.txt");
        int X = 0;

        if (File.is_open()) {
            File >> X;
            File.close();
        }
        else {
            std::cerr << "Unable to open file." << std::endl;
        }
        if (X == 1) {
            int ret_menu = Menu::ShowMenu(g_screen, font_time);
            if (ret_menu == 0)
            {
                Continue = false;
                Game::ResetThreatGame();
            }
            else if (ret_menu == 1)
            {
                Continue = true;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            int ret_menu = Menu::ShowMenuNoCon(g_screen, font_time);
            if (ret_menu == 0)
            {
                Continue = false;
                Game::ResetThreatGame();
            }
            else
            {
                return 0;
            }
        }

        if (LoadBackground() == false)
        {
            return -1;
        }
        game_map.LoadMap("map/map01.dat");
        game_map.LoadTiles(g_screen);


        p_player.LoadImg("img//player_right.png", g_screen);
        p_player.set_clips();

        PlayerMoney player_money;
        player_money.Init(g_screen);
        player_money.SetPos(SCREEN_WIDTH * 0.5 - 300, 8);
        BossLives boss_power;
        boss_power.Init(g_screen);
        boss_power.SetPos(SCREEN_WIDTH * 0.5 - 50, 50);
        PlayerBrave player_brave;
        player_brave.Init(g_screen);
        player_brave.SetPos(SCREEN_WIDTH * 0.5 + 200, 10);

        std::vector<ThreatsObject*>threats_list = MakeThreatsList();
        std::vector<BulletObject> storm(9);
        for (int i = 0; i < storm.size(); i++)
        {
            storm[i].LoadImg("img//boss bullet.png", g_screen);
            storm[i].set_bullet_dir(BulletObject::DIR_DOWN);
            storm[i].SetRect(64 + i * 64 * 3, -64);
            storm[i].set_x_val(0);
            if (i % 2 == 0)
            {
                storm[i].set_y_val(8);
            }
            else storm[i].set_y_val(10);
        }
        ExplosionObject exp_player;
        bool pRet = exp_player.LoadImg("img//exp3.png", g_screen);
        if (!pRet) return -1;
        exp_player.set_clips();
        ExplosionObject exp_threat;
        bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
        if (!tRet) return -1;
        exp_threat.set_clips();


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
        TextObject boss_live_text;
        boss_live_text.SetColor(TextObject::RED_TEXT);
        TextObject threat;
        threat.SetColor(TextObject::WHITE_TEXT);
        bool flag_threat = false;


        if (num_boss != 0)
        {
            bool ret = bossObject.LoadImg("img//threat_level.png", g_screen);
            bossObject.set_clips();
            int xPosBoss = MAX_MAP_X* TILE_SIZE - SCREEN_WIDTH * 0.6;//1200;
            bossObject.set_xpos(xPosBoss);
            bossObject.set_ypos(10);
            BulletObject* b_bullet = new BulletObject();
            bossObject.InitBullet(b_bullet, g_screen);
        }
        BossMini threat1, threat2;
        bool ret1 = threat1.LoadImg("img//threat_level.png", g_screen);
        bool ret2 = threat2.LoadImg("img//threat_level.png", g_screen);
        threat1.set_clips();
        threat2.set_clips();
        threat1.set_xpos(bossObject.get_x_pos() + 64);
        threat2.set_xpos(bossObject.get_x_pos() - 64);
        threat1.set_ypos(bossObject.get_y_pos());
        threat2.set_ypos(bossObject.get_y_pos());
        threat1.set_speed(4);
        threat2.set_speed(5);
        if (Continue)
        {
            int mnc, br;
            float xpos, ypos, xposboss, yposboss;
            Game::LoadGame("Game.txt", mnc, br, xpos, ypos, num_boss, num_die, mark_value, timegame,showboss,xposboss, yposboss);
            p_player.set_x_pos(xpos);
            p_player.set_y_pos(ypos);
            p_player.SetBrave(br);
            p_player.SetMoney(mnc);
            bossObject.set_xpos(xposboss);
            bossObject.set_ypos(yposboss);
            std::ifstream file("Threat.txt");
            int pos;
            while (file >> pos)
            {
                threats_list.erase(threats_list.begin() + pos);
            }
            file.close();
            Map continuemap = game_map.getMap();
            Game::LoadMapFromTxt("map//mapcontinue.txt", continuemap);
            game_map.SetMap(continuemap);
        }

        PlayerLives player_power;
        player_power.Init(g_screen, num_die);
        ImpTimer start_game;
        start_game.start();

        while (!is_quit)
        {
            fps_timer.start();
            Map map_data = game_map.getMap();
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    Game::SaveGame("Game.txt", p_player.GetMoneyCount(), p_player.GetNumBrave()
                                    ,p_player.get_x_pos(), p_player.get_y_pos(), num_boss, num_die, mark_value, val_time,
                                     showboss,bossObject.get_x_pos(),bossObject.get_y_pos());
                    Game::SaveMap("map//mapcontinue.txt", map_data);
                    std::ofstream file("HaveContinue.txt");
                    if (file.is_open())
                    {
                        int x = 1;
                        file << x << "\n";
                        file.close();
                    }
                    else
                    {
                        std::cerr << "Unable to save map to file " << std::endl;
                    }
                    is_quit = true;
                    Playgame = false;
                }
                if (g_event.type == SDL_KEYDOWN)
                {
                    switch (g_event.key.keysym.sym)
                    {
                    case SDLK_p:
                        int ret = Menu::ShowPause(g_screen, font_time,&start_game);
                        if (ret == 1)
                        {
                            Game::SaveGame("Game.txt", p_player.GetMoneyCount(), p_player.GetNumBrave()
                                           ,p_player.get_x_pos(), p_player.get_y_pos(), num_boss, num_die, mark_value, val_time, showboss,
                                           bossObject.get_x_pos(),bossObject.get_y_pos());
                            Game::SaveMap("map//mapcontinue.txt", map_data);
                            std::ofstream file("HaveContinue.txt");
                            if (file.is_open())
                            {
                                int x = 1;
                                file << x << "\n";
                                file.close();
                            }
                            else
                            {
                                std::cerr << "Unable to save map to file " << std::endl;
                            }
                            is_quit = true;
                        }
                        else if (ret == 2)
                        {
                            Game::SaveGame("Game.txt", p_player.GetMoneyCount(), p_player.GetNumBrave()
                                           ,p_player.get_x_pos(), p_player.get_y_pos(), num_boss, num_die, mark_value, val_time,
                                           showboss, bossObject.get_x_pos(), bossObject.get_y_pos());
                            Game::SaveMap("map//mapcontinue.txt", map_data);
                            std::ofstream file("HaveContinue.txt");
                            if (file.is_open())
                            {
                                int x = 1;
                                file << x << "\n";
                                file.close();
                            }
                            else
                            {
                                std::cerr << "Unable to save map to file " << std::endl;
                            }
                            is_quit = true;
                            Playgame = false;
                        } 
                        start_game.unpaused();
                        break;
                    }
                }
                p_player.HandelInputAction(g_event, g_screen);
            }
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            g_background.Render(g_screen, NULL);

            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.DoPlayer(map_data);
            if (p_player.get_brave() && p_player.GetNumBrave() > 0)
            {
                p_player.DoBrave(map_data);
            }
            if (p_player.get_out_area())
            {
                num_die--;
                player_power.Decrease();
                player_power.Render(g_screen);
               
            }
            if (num_die <= 0)
            {
                std::ofstream file ("HaveContinue.txt");
                if (file.is_open())
                {
                    int x = 0;
                    file << x << "\n";
                    file.close();
                }
                else
                {
                    std::cerr << "Unable to save map to file " << std::endl;
                }
                int ret = Menu::ShowGameOver(g_screen, font_time);
                if (ret == 1) {
                    close();

                    is_quit = true;
                    Playgame = false;
                    break;
                }
                else
                {
                    close();

                    is_quit = true;

                }

            }
            p_player.Show(g_screen);
            p_player.HandleBullet(g_screen, map_data);
            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);
            //DrawGeometric
            GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
            ColorData color_data(94, 94, 94);
            Geometric::RenderRectange(rectangle_size, color_data, g_screen);

            GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
            ColorData color_data2(255, 255, 255);
            Geometric::RenderOutline(outLineSize, color_data2, g_screen);
            //Icons
            player_power.Show(g_screen);
            player_money.Show(g_screen);
            player_brave.Show(g_screen);

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
                        p_threat->ImpMoveType(g_screen, p_player.get_x_pos(), p_player.get_y_pos());
                        p_threat->DoPlayer(map_data, g_screen);
                        if (p_threat->get_on_ground())
                        {
                            p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, p_player.get_x_pos(), p_player.get_y_pos(), map_data);
                        }
                        p_threat->Show(g_screen);
                        SDL_Rect rect_player = p_player.GetRectFrame();
                        bool bCol1 = false;
                        if (p_player.get_threat_can_fire())
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
                                num_die--;
                                if (num_die != 0)
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
                                    std::ofstream file("HaveContinue.txt");
                                    if (file.is_open())
                                    {
                                        int x = 0;
                                        file << x << "\n";
                                        file.close();
                                    }
                                    else
                                    {
                                        std::cerr << "Unable to save map to file " << std::endl;
                                    }
                                    int ret = Menu::ShowGameOver(g_screen, font_time);
                                    if (ret == 1) {
                                        close();
                                        
                                        is_quit = true;
                                        Playgame = false;
                                    }
                                    else
                                    {
                                        close();
                                        
                                        is_quit = true;
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
            for (int r = 0; r < bullet_arr.size(); r++)
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
                                        Game::SaveDieThreat(t);
                                        obj_threat->Free();
                                        threats_list.erase(threats_list.begin() + t);
                                        flag_threat = false;
                                    }
                                    else if (p_bullet->get_bullet_type() == BulletObject::LASER_BULLET &&
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
                                        Game::SaveDieThreat(t);
                                        obj_threat->Free();
                                        threats_list.erase(threats_list.begin() + t);
                                        flag_threat = false;
                                    }
                                    else flag_threat = true;
                                    p_player.RemoveBullet(r);
                                }
                            }
                        }
                    }
                }
            }
            //Show Boss
            int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
            if (val < SCREEN_WIDTH) { showboss = true; }
           if(showboss)
           {          
                if (num_boss > 0)
                {

                    boss_power.Show(g_screen);
                    std::string boss_power_str = std::to_string(num_boss);
                    boss_live_text.SetText(boss_power_str);
                    boss_live_text.loadFromRenderedText(font_time, g_screen);
                    boss_live_text.RenderText(g_screen, SCREEN_WIDTH * 0.5, 57);
                    bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
                    bossObject.ImpMoveType(p_player.get_x_pos());
                    bossObject.DoPlayer(map_data);
                    game_map.SetMap(map_data);
                    game_map.DrawMap(g_screen);
                    bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, p_player.get_x_pos(), p_player.get_y_pos(), map_data);
                    bossObject.Show(g_screen);
                    SDL_Rect rect_player = p_player.GetRectFrame();
                    if (p_player.get_threat_can_fire())
                    {
                        bool BossCol1 = false;
                        std::vector<BulletObject*>bBullet_list = bossObject.get_bullet_list();
                        for (int jj = 0; jj < bBullet_list.size(); jj++)
                        {
                            BulletObject* pt_bullet = bBullet_list.at(jj);
                            if (pt_bullet)
                            {
                                BossCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);

                            }
                            if (BossCol1)
                            {
                                break;
                            }
                        }
                        SDL_Rect rect_boss = bossObject.GetRectFrame();
                        bool BossCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_boss);
                        if (BossCol1 == true || BossCol2 == true)
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
                            num_die--;
                            if (num_die != 0)
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

                                is_quit = true;
                                std::ofstream file("HaveContinue.txt");
                                if (file.is_open())
                                {
                                    int x = 0;
                                    file << x << "\n";
                                    file.close();
                                }
                                else
                                {
                                    std::cerr << "Unable to save map to file " << std::endl;
                                }
                                int ret = Menu::ShowGameOver(g_screen, font_time);
                                if (ret == 1) {
                                    close();

                                    is_quit = true;
                                    Playgame = false;
                                }
                                else
                                {
                                    close();

                                    is_quit = true;
                                }
                            }
                        }
                    }
                    std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
                    for (int r = 0; r < bullet_arr.size(); r++)
                    {
                        BulletObject* p_bullet = bullet_arr.at(r);
                        if (p_bullet != NULL)
                        {
                            SDL_Rect BRect;
                            BRect.x = bossObject.GetRect().x;
                            BRect.y = bossObject.GetRect().y;
                            BRect.w = bossObject.get_width_frame();
                            BRect.h = bossObject.get_height_frame();
                            SDL_Rect bRect = p_bullet->GetRect();
                            bool bCol = SDLCommonFunc::CheckCollision(bRect, BRect);
                            if (bCol)
                            {
                                num_boss--;
                                for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                                {
                                    int x_pos = bossObject.GetRect().x - frame_exp_width * 0.5;
                                    int y_pos = bossObject.GetRect().y - frame_exp_heigh * 0.5;
                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos, y_pos);
                                    exp_threat.Show(g_screen);
                                }

                                bossObject.Free();

                                p_player.RemoveBullet(r);
                            }
                        }
                    }
                    threat1.SetMapXY(map_data.start_x_, map_data.start_y_);
                    threat1.ImpMoveType(g_screen,p_player.get_x_pos());
                    threat1.DoPlayer(map_data);
                    game_map.SetMap(map_data);
                    game_map.DrawMap(g_screen);
                    threat1.Show(g_screen);
                    if(threat1.get_on_ground()){
                    SDL_Rect rect_player1 = p_player.GetRectFrame();
                    if (p_player.get_threat_can_fire())
                    {

                        SDL_Rect rect_boss = threat1.GetRectFrame();
                        bool BossCol2 = SDLCommonFunc::CheckCollision(rect_player1, rect_boss);
                        if (BossCol2 == true)
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
                            num_die--;
                            if (num_die != 0)
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

                                is_quit = true;
                                std::ofstream file("HaveContinue.txt");
                                if (file.is_open())
                                {
                                    int x = 0;
                                    file << x << "\n";
                                    file.close();
                                }
                                else
                                {
                                    std::cerr << "Unable to save map to file " << std::endl;
                                }
                                int ret = Menu::ShowGameOver(g_screen, font_time);
                                if (ret == 1) {
                                    close();

                                    is_quit = true;
                                    Playgame = false;
                                }
                                else
                                {
                                    close();

                                    is_quit = true;
                                }
                            }
                        }
                    }
                    std::vector<BulletObject*> bullet_arr1 = p_player.get_bullet_list();
                    for (int r = 0; r < bullet_arr1.size(); r++)
                    {
                        BulletObject* p_bullet = bullet_arr1.at(r);
                        if (p_bullet != NULL)
                        {
                            SDL_Rect BRect;
                            BRect.x = threat1.GetRect().x;
                            BRect.y = threat1.GetRect().y;
                            BRect.w = threat1.get_width_frame();
                            BRect.h = threat1.get_height_frame();
                            SDL_Rect bRect = p_bullet->GetRect();
                            bool bCol = SDLCommonFunc::CheckCollision(bRect, BRect);
                            if (bCol)
                            {
                                for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                                {
                                    int x_pos = threat1.GetRect().x - frame_exp_width * 0.5;
                                    int y_pos = threat1.GetRect().y - frame_exp_heigh * 0.5;
                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos, y_pos);
                                    exp_threat.Show(g_screen);
                                }

                                threat1.set_clips();
                                threat1.set_xpos(bossObject.get_x_pos() + 64);
                                threat1.set_ypos(bossObject.get_y_pos());
                                threat1.set_think_time(180);
                                threat1.set_on_ground(false);
                                p_player.RemoveBullet(r);
                            }
                        }
                    }
                }
                    
                    threat2.SetMapXY(map_data.start_x_, map_data.start_y_);
                    threat2.ImpMoveType(g_screen, p_player.get_x_pos());
                    threat2.DoPlayer(map_data);
                    game_map.SetMap(map_data);
                    game_map.DrawMap(g_screen);
                    threat2.Show(g_screen);
                    if (threat2.get_on_ground()) {
                        SDL_Rect rect_player2 = p_player.GetRectFrame();
                        if (p_player.get_threat_can_fire())
                        {

                            SDL_Rect rect_boss = threat2.GetRectFrame();
                            bool BossCol2 = SDLCommonFunc::CheckCollision(rect_player2, rect_boss);
                            if (BossCol2 == true)
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
                                num_die--;
                                if (num_die != 0)
                                {
                                    p_player.SetRect(0, 0);
                                    p_player.set_comebeack_time(120);
                                    SDL_Delay(500);
                                    player_power.Decrease();
                                    player_power.Render(g_screen);
                                    continue;
                                }
                                else
                                {
                                    player_power.Decrease();
                                    player_power.Render(g_screen);

                                    is_quit = true;
                                    std::ofstream file("HaveContinue.txt");
                                    if (file.is_open())
                                    {
                                        int x = 0;
                                        file << x << "\n";
                                        file.close();
                                    }
                                    else
                                    {
                                        std::cerr << "Unable to save map to file " << std::endl;
                                    }
                                    int ret = Menu::ShowGameOver(g_screen, font_time);
                                    if (ret == 1) {
                                        close();

                                        is_quit = true;
                                        Playgame = false;
                                    }
                                    else
                                    {
                                        close();

                                        is_quit = true;
                                    }
                                }
                            }
                        }
                        std::vector<BulletObject*> bullet_arr2 = p_player.get_bullet_list();
                        for (int r = 0; r < bullet_arr2.size(); r++)
                        {
                            BulletObject* p_bullet = bullet_arr2.at(r);
                            if (p_bullet != NULL)
                            {
                                SDL_Rect BRect;
                                BRect.x = threat2.GetRect().x;
                                BRect.y = threat2.GetRect().y;
                                BRect.w = threat2.get_width_frame();
                                BRect.h = threat2.get_height_frame();
                                SDL_Rect bRect = p_bullet->GetRect();
                                bool bCol = SDLCommonFunc::CheckCollision(bRect, BRect);
                                if (bCol)
                                {
                                    for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                                    {
                                        int x_pos = threat2.GetRect().x - frame_exp_width * 0.5;
                                        int y_pos = threat2.GetRect().y - frame_exp_heigh * 0.5;
                                        exp_threat.set_frame(ex);
                                        exp_threat.SetRect(x_pos, y_pos);
                                        exp_threat.Show(g_screen);
                                    }

                                    threat2.set_clips();
                                    threat2.set_xpos(bossObject.get_x_pos() + 64);
                                    threat2.set_ypos(bossObject.get_y_pos());
                                    threat2.set_think_time(180);
                                    threat2.set_on_ground(false);
                                    p_player.RemoveBullet(r);
                                }
                            }
                        }
                    }
                }
               

            }
            //Win
            if (p_player.get_x_pos() >= map_data.max_x_ - p_player.get_frame_width() * 2 && p_player.get_on_ground())
            {
                if (num_boss <= 0)
                {

                    is_quit = true;
                    std::ofstream file("HaveContinue.txt");
                    if (file.is_open())
                    {
                        int x = 0;
                        file << x << "\n";
                        file.close();
                    }
                    else
                    {
                        std::cerr << "Unable to save map to file " << std::endl;
                    }

                    int ret = Menu::ShowVitory(g_screen, font_time);
                    if (ret == 1) {
                        close();
                        
                        is_quit = true;
                        Playgame = false;
                    }
                    else
                    {
                        close();
                        
                        is_quit = true;
                    }
                }
                else
                {
                    threat.SetText("BAN CAN TIEU DIET BOSS!");
                    threat.loadFromRenderedText(font_time, g_screen);
                    threat.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 150, 100);
                }
            }
            //Show game time
            std::string str_time = "TIME: ";
            Uint32 time_val = start_game.get_ticks() / 1000;
            val_time = timegame - time_val;
            Uint32 minutes = val_time / 60; // Số phút
            Uint32 seconds = val_time % 60; // Số giây còn lại
            if (val_time % 50 == 0 && val_time != 300)
            {
                for (int i = 0; i < storm.size(); i++)
                {
                    storm[i].set_is_move(true);
                    storm[i].SetRect(64 + i * 64 * 3, -64);
                }
            }
            for (int i = 0; i < storm.size(); i++)
            {
                if (storm[i].get_is_move())
                {
                    storm[i].HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT, map_data);
                    storm[i].Render(g_screen);
                }
            }
            if(p_player.get_x_pos()>=map_data.start_x_+SCREEN_WIDTH-TILE_SIZE/4|| p_player.get_x_pos() <= map_data.start_x_ )
            for (int i = 0; i < storm.size(); i++)
            {
                storm[i].set_is_move(false);
            }
            SDL_Rect rect_player = p_player.GetRectFrame();
            bool Col1 = false;
            for (int i = 0; i < storm.size(); i++)
            {
                if (storm[i].get_is_move())
                {
                    Col1 = SDLCommonFunc::CheckCollision(storm[i].GetRect(), rect_player);
                    if (Col1)
                    {
                        break;
                    }
                }
            }
            if (Col1 == true)
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
                num_die--;
                if (num_die != 0)
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
                    std::ofstream file("HaveContinue.txt");
                    if (file.is_open())
                    {
                        int x = 0;
                        file << x << "\n";
                        file.close();
                    }
                    else
                    {
                        std::cerr << "Unable to save map to file " << std::endl;
                    }
                    int ret = Menu::ShowGameOver(g_screen, font_time);
                    if (ret == 1) {
                        close();

                        is_quit = true;
                        Playgame = false;
                    }
                    else
                    {
                        close();

                        is_quit = true;
                    }
                }
            }
            if (val_time <= 0)
            {
                std::ofstream file("HaveContinue.txt");
                if (file.is_open())
                {
                    int x = 0;
                    file << x << "\n";
                    file.close();
                }
                else
                {
                    std::cerr << "Unable to save map to file " << std::endl;
                }
                is_quit = true;
                int ret = Menu::ShowGameOver(g_screen, font_time);
                if (ret == 1) {
                    is_quit = true;
                    Playgame = false;
                    break;
                }
                else {
                    is_quit = true;
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

            if (flag_threat)
            {
                threat.SetText("HAY BAM L DE DOI DAN!");
                threat.loadFromRenderedText(font_time, g_screen);
                threat.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 100);
            }

            if (num_brave == 0)
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
                for (int i = 0; i < p_threats->get_bullet_list().size(); i++)
                {
                    p_threats->RemoveBullet(i);
                }
                p_threats->Free();
                p_threats = NULL;
            }
        }
        for (int i = 0; i < bossObject.get_bullet_list().size(); i++)
        {
            bossObject.RemoveBullet(i);
        }
        if (!threats_list.empty())
        {
            threats_list.clear();
        }
        bossObject.Free();
        close();
    }
    return 0;
}
