#include "Tuto.h"
#include "system.h"
#include "Game.h"
#include "Nigirou.h"
#include "Player.h"
#include "FoodManager.h"

#define TUTO_BG_PATH PATH"tuto.bmp"		//チュートリアルの背景画像パス

Tuto::Tuto()
{
	m_bmpdata->LoadBitMap(TUTO_BG_PATH);//背景の読み込み
}

Tuto::~Tuto()
{
	
}

void Tuto::Init()
{
}

void Tuto::Update()
{
	
	
	
	if (inport(PK_ENTER))
	{//ENTERキーが押されたら
		PLAYER->Init();//ゲームイニットをかける
		FOODMANAGER->Init();//フードマネージャーイニットをかける
		reinport();//入力のリセット
		GAME->ChangeScene(new Nigirou());//ゲームシーンをNigirouに変更
	}
}

void Tuto::Draw()
{
	m_bmpdata->OutPutBMP(0, 0);//背景の描画
}
