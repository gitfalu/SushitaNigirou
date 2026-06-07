#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)//どこでメモリリークが起こっているか表示してくれる設定

#pragma once
//conioexをインクルード
#define CONIOEX
#include "conioex.h"



#define FPS (60)//フレームレート
#define SCREEN_WIDTH (160)//画面の幅
#define SCREEN_HEIGHT (90)//画面の高さ


#define CONVE_HIGH_POSY (6)//コンベアのY座標
#define CONVE_WIDTH (112)//コンベアの幅
#define CONVE_HEIGHT (16)//コンベアの高さ


#define FOODTYPE (7)//食料の種類数

