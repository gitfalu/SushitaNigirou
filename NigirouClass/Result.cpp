#include "Result.h"
#include "system.h"
#include "Game.h"
#include "Title.h"
#include "Player.h"
#include "ScoreManager.h"

Result::Result()
{
}

Result::~Result()
{
}

void Result::Init()
{
}

void Result::Update()
{
	PLAYER->Update();//プレイヤーの更新


	if (inport(PK_ENTER))
	{//エンターキーが入力されたら
		SCOREMANAGER->Nigirou();//Nigirou処理に切り替える
		SCOREMANAGER->Init();//ScoreManagerの初期化
		reinport();
		GAME->ChangeScene(new Title());//タイトルシーンに切り替え
	}
}

void Result::Draw()
{
	SCOREMANAGER->Draw();//スコアマネージャーの描画
	PLAYER->Draw();//プレイヤーの描画
}
