
#include "Title.h"
#include "system.h"
#include "Game.h"
#include "Tuto.h"

#define TITLE_BG_PATH PATH"title.bmp"//タイトル画面の背景


Title::Title()
{
	m_bmpdata->LoadBitMap(TITLE_BG_PATH);//背景の読み込み
}

Title::~Title()
{
}

void Title::Init()
{

}

void Title::Update()
{
	if (inport(PK_ENTER))
	{//エンターキーが入力されたら
		reinport();
		GAME->ChangeScene(new Tuto());//チュートリアルへ
	}

}

void Title::Draw()
{
	m_bmpdata->OutPutBMP(0, 0);//背景の描画
}
