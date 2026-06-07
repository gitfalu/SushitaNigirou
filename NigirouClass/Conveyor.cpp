#include "Conveyor.h"
#include "Game.h"


#define MOVE_SPEED		(0.4f)		//コンベアの作動速度
#define CONVE_HIGH_Y	(6)			//コンベアの情報位置座標
#define CONVE_WIDTH		(112)		//コンベアの幅
#define CONVE_HEIGHT	(16)		//一つのコンベアの高さ

Conveyor::Conveyor()
{
	
	Init();//初期化処理を呼び出し
}

Conveyor::~Conveyor()
{
}

void Conveyor::Init()
{
	int nVec = 1;// コンベアの作動方向 1:右  -1:左
	int i;
	srand(time(NULL));// 乱数の初期化
	for (i = 0; i < rand() % 10; i++)nVec *= -1;// ランダムに方向を決定
	for (i = 0; i < MAX_CONVEYOR; ++i)
	{
		m_MoveVec[i] = nVec;// コンベアの方向をセット
		nVec *= -1;// 方向を反転
	}
	m_MoveSpeed = MOVE_SPEED;// コンベアの速度をセット
}

void Conveyor::Draw()
{
	
	int i;
	int x, y;
	

	for (i = 0; i < MAX_CONVEYOR; ++i)
	{// コンベアの描画
		for (y = 0; y < CONVE_HEIGHT; y++)
		{// 16ドットの高さ
			for (x = 0; x < CONVE_WIDTH; x++)
			{// 112ドットの幅
				if (y == 0 || y == CONVE_HEIGHT - 1 ||
					x % 8 == 0)
				{// 枠の描画
					GAME->SetScreen(x + 2, y + CONVE_HIGH_Y + i * CONVE_HEIGHT, 7);// 枠の描画
					continue;
				}
				if (y >= 6 && y <= 10)
				{// ベルト部分の描画
					if (m_MoveVec[i] == 1)// 右向き
						GAME->SetScreen(x + 2, y + CONVE_HIGH_Y + i * CONVE_HEIGHT, 
							image[y - 6][x % 8 - 1] + i % 2);// ベルトの描画
					else// 左向き
						GAME->SetScreen(x + 2, y + CONVE_HIGH_Y + i * CONVE_HEIGHT, 
							image[y - 6][7 - x % 8] + i % 2);// ベルトの描画
					continue;
				}
				GAME->SetScreen(x + 2, y + CONVE_HIGH_Y + i * CONVE_HEIGHT, i % 2 + 8);// 矢印部分以外の描画
			}
		}
	}
}

void Conveyor::Update()
{

}

float Conveyor::GetMoveVelo(int pos)
{
	return m_MoveVec[pos] * MOVE_SPEED;// コンベアの速度を返す
}
