#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include"CommonFunc.h"
#include"BaseObject.h"
#include"BulletObject.h"
#include<vector>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 18

class MainObject :public BaseObject
{
public:
	enum WalkType
	{
		WALK_NONE =0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
	};
	MainObject();
	~MainObject();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map&map_data);
	void SetMapXY(const int&map_x, const int&map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnmap(Map& map_data) const;
	void UpdateImagePlayer(SDL_Renderer* des);
	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list()const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des,Map& map_data);
	void ChangeBullet(const int& sellectbullet);
	void RemoveBullet(const int& idx);
	SDL_Rect GetRectFrame();
	void IncreaseMoney();
	float get_x_pos()const { return x_pos_; }
	float get_y_pos()const { return y_pos_; }
	float get_x_val() const { return x_val_; }
	void set_comebeack_time(const int& cb_time) { come_back_time_ = cb_time; }
	int get_frame_width() { return width_frame_; }
	int get_frame_height() { return height_frame_; }

	int GetMoneyCount() { return money_count; }
	int GetNumBrave() { return num_brave; }
	void SetMoney(int mn) { money_count = mn; }
	void SetBrave(int br) { num_brave = br; }
	void set_x_pos(const float& xps) { x_pos_ = xps; }
	void set_y_pos(const float& yps) { y_pos_ = yps; }
	void set_on_ground(bool x) { on_ground = x; }
	void set_doublejump(bool x) { doublejump = x; }
	bool get_threat_can_fire() { return Threat_can_fire; }
	bool get_out_area() { return out_area; }
	bool get_on_ground() { return on_ground; }

	void DoBrave(Map& map_data);
	bool get_brave() { return brave; }

	void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
	void set_input_right(const int& ipLeft) { input_type_.right_ = ipLeft; }
	void set_input_down(const int& ipLeft) { input_type_.down_ = ipLeft; }

	void Trap(Map& map_data,const int& x, const int& y);
	void Trap2(Map& map_data, const int& x, const int& y);
private:
	bool out_area;
	bool Threat_can_fire;
	int money_count;
	int num_brave;
	std::vector<BulletObject*> p_bullet_list_;
	float x_val_; 
	float y_val_;
	
	float x_pos_;
	float y_pos_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground;
	int map_x_;
	int map_y_;
	int come_back_time_;
	unsigned int sellect_bullet_;
	bool doublejump;
	bool brave;

};


#endif // !MAIN_OBJECT_H_
