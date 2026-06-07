#include "Score.h"
#include "Game.h"

Score::Score()
{
	m_Score = 0;//スコア初期化
	m_NumberLimit = 0;//最大値初期化
	m_NumberLimitDigit = 1;//桁数初期化
}

Score::~Score()
{
	
}

void Score::Init()
{
	//m_Score = 0;//スコア初期化
}

void Score::SetLimit(int LimitNum,float posX,float posY)
{
	m_NumberLimitDigit = 1;//桁数初期化
	m_NumberLimit = LimitNum;//最大値設定
	for (int i = 0;LimitNum > 9;)
	{//桁数を調べる
		++m_NumberLimitDigit;//桁数をカウント
		LimitNum /= 10;
	}
	m_position.x = posX;//スコア表示位置設定
	m_position.y = posY;//スコア表示位置設定
}

void Score::Draw()
{
	int DrawNum;//描画する文字
	int ScoreStack = m_Score;//スコアの桁数を調べるための変数
	for (int i = m_NumberLimitDigit - 1; i >= 0; --i)
	{
		DrawNum = (ScoreStack % 10);//一の位の数字を取得
		for (int y = 0; y < SCORE_HEIGHT; y++)
		{
			for (int x = 0; x < SCORE_WIDTH; x++)
			{///スコアの描画
				GAME->SetScreen(m_position.x + (SCORE_WIDTH * i) + x,
					m_position.y + y, m_Numbers[DrawNum][x + y * SCORE_WIDTH]);//スコアの描画
			}
		}
		ScoreStack /= 10;//次の桁へ
	}
}

void Score::Update()
{
	
}

void Score::AddScore(int add)
{
	m_Score += add;//スコア加算
	if (m_Score > m_NumberLimit)
	{
		m_Score = m_NumberLimit;//上限を超えたら上限値にする
	}
}
