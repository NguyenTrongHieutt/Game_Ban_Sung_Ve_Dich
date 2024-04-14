#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_


#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include"MainObject.h"

#define WIDHT_THREAT 44;
#define HEIGHT_THREAT 50;

#define THREATS_GRAVITY_SPEED 0.8
#define THREATS_MAX_FALL_SPEED 10

#define THREAT_SPEED 3
#define PLAYER_HIGHT_VAL 18;
#define TRAP_SPEED 9

#define THREATS_NUM_FRAME 8


class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();
    void set_x_val(const float& xp) { x_val_ = xp; }
    void set_y_val(const float& yp) { y_val_ = yp; }

    void set_x_pos(const float& xps) { x_pos_ = xps; }
    void set_y_pos(const float& yps) { y_pos_ = yps; }
    float get_x_pos()const { return x_pos_; }
    float get_y_pos()const { return y_pos_; }
 
    void SetMapXY(const int& map_x, const int& map_y) { map_x_ = map_x, map_y_ = map_y; }
  
    void CheckToMap(Map& g_map, SDL_Renderer* screen);
    void CheckToMap2(Map& map_data, SDL_Renderer* screen);

    void DoPlayer(Map& g_map, SDL_Renderer* screen);
    void DoPlayer2(Map& gMap, SDL_Renderer* screen);

    void Show(SDL_Renderer* des);
    void Show2(SDL_Renderer* des);

    bool LoadImg(std::string path, SDL_Renderer* screen);
    bool LoadImg2(std::string path, SDL_Renderer* screen);
    void set_clips();

    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    
    void set_type_move(const int& typeMove)
    {
        type_move_ = typeMove;
    }
    void SetAnimationPos(const int& pos_a, const int& pos_b)
    {
        animation_a_ = pos_a;
        animation_b_ = pos_b;
    }
    void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
    void ImpMoveType(SDL_Renderer* screen, const float& x, const float& y);
    void ImpMoveType2(SDL_Renderer* screen, const float& x, const float& y);
    void InitThreats();
    std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
    void set_bullet_list(const std::vector<BulletObject*>& am_list) { bullet_list_ = am_list; }
    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void InitBulletTrap(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit,
                    const float& x2,const float& y2,Map& map_data );
    void MakeBulletTrap(SDL_Renderer* des, const int& x_limit,
                        const int& y_limit, const float& x2,
                        const float& y2, Map& map_data);
    void RemoveBullet(const int& idx);
    SDL_Rect GetRectFrame();
    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_TH = 1,
    };
    int get_typemove() { return type_move_; }
    bool get_on_ground(){return on_ground;}
private:
    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    bool is_alive_;
    bool is_stop_bullet_;
    float x_pos_;
    float y_pos_;
    int on_ground;
    int come_back_time_;
    int think_time_;
    Input input_type_;
    SDL_Rect frame_clip_[THREATS_NUM_FRAME];
    int width_frame_;
    int height_frame_;
    int frame_;
    int animation_a_;
    int animation_b_;
    int type_move_;
    std::vector<BulletObject*> bullet_list_;
};

#endif //THREATS_OBJECT_H_