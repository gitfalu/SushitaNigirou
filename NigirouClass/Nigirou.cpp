#include "Nigirou.h"
#include "system.h"
#include "Game.h"
#include "Result.h"
#include "Player.h"
#include "FoodManager.h"
#include "ScoreManager.h"

Nigirou::Nigirou()
{
	m_Timer = 60;//タイマー初期化
	m_TimerFrame = 0;//タイマーフレーム初期化
}

Nigirou::~Nigirou()
{
}

void Nigirou::Init()
{
}

void Nigirou::Update()
{
	m_TimerFrame++;//フレーム数増加
	if (m_TimerFrame / 60 >= 1)
	{//60フレーム(１秒)ごとに
		--m_Timer;//タイマー減少
		m_TimerFrame = 0;//フレーム数リセット
	}
	PLAYER->Update();//プレイヤーの更新
	FOODMANAGER->Update();//フードマネージャーの更新
	m_Timer += SCOREMANAGER->TimerCntUp();//タイマーのカウントを増やす

	if (m_Timer <= 0)
	{//タイマーが0以下になったら
		PLAYER->InitResult();//リザルトイニットをかける
		SCOREMANAGER->Result();//リザルト処理に切り替える
		SCOREMANAGER->Init();//ScoreManagerの初期化
		reinport();
		GAME->ChangeScene(new Result());//リザルトシーンに切り替え
	}
}

void Nigirou::Draw()
{
	PLAYER->Draw();//プレイヤーの描画
	FOODMANAGER->Draw();//フードの描画
	SCOREMANAGER->Draw();//スコアの描画
	for (int i = 0; i < m_Timer; ++i)
	{//残り時間の表示
		GAME->SetScreen(1 + i, 2, GREEN);
	}
}
