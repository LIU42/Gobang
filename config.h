#ifndef __CONFIG_H__
#define __CONFIG_H__

#define TITLE "Gobang"
#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 650
#define GAME_FPS 10
#define IMG_FORMAT SDL_PIXELFORMAT_RGBA32

#define FONT_SIZE 18
#define TEXT_RECT_WIDTH 200
#define TEXT_RECT_HEIGHT 18
#define TEXT_MAX_LEN 30
#define TEXT_COLOR { 0, 0, 0 }

#define TABLE_LARGE 19
#define BLOCK 30
#define BORDER 10
#define REGION_BORDER 25

#define PLAYING 0
#define OVER 1
#define EXIT 2

#define BLACK_CHESS 'B'
#define WHITE_CHESS 'W'
#define EMPTY_CHESS '0'
#define SELF_CHESS 'S'
#define OPPOSITE_CHESS 'O'
#define NOW_CHESS 'N'

#define BLACK_SIDE 1
#define WHITE_SIDE -1
#define NONE_SIDE 0
#endif