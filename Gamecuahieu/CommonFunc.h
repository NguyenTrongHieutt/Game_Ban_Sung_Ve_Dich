#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_
#include<windows.h>
#include<string>
#include<cmath>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_player[6];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_coin[2];
static Mix_Chunk* g_sound_event[3];
static Mix_Music* g_sound_music[3];
static Mix_Chunk* g_sound_endgame[2];
//audio
const int TOTAL_CHANNEL = 8;
const int CHANNEL_GUN= 0;
const int CHANNEL_EXP = 1;
const int CHANNEL_COIN = 3;
const int CHANNEL_JUMP = 4;
const int CHANNEL_EVENT = 5;
const int CHANNEL_BOSS1 = 6;
const int CHANNEL_BOSS2 = 7;
//screen
const int FRAME_PER_SECOND = 25.2;//fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0			
#define STATE_MONEY 4
#define ITEM_BRAVE 11
#define BRAVE 10
#define TIMETOTAL 600
#define TIMESHIELD 60
#define MARKICRLIVE 500
#define NUMBOSS 10
#define NUMDIE 3
#define FLAG 15

typedef struct Map 
{
	int start_x_;
	int start_y_;
	
	int max_x_;
	int max_y_;
	
	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;
};
typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};

namespace SDLCommonFunc
{
	bool CheckCollision(const  SDL_Rect& object1, const SDL_Rect& object2);
	bool IsInside(const SDL_Rect& rectA, const SDL_Rect& rectB);
}

#endif // !COMMON_FUNCTION_H_
