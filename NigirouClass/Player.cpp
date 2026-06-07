#include "Player.h"
#include "Game.h"
#include "bitmap.h"
#include "FoodManager.h"

Player* Player::s_instance = nullptr;


#define LIMIT_UP			(0)						//コンベアの上側移動制限	
#define LIMIT_DOWN			(3)						//コンベアの下側移動制限
#define PLAYERUPIMGPATH		PATH"chefup.bmp"		//プレイヤーがレバーを上げているときの画像BMPファイル
#define PLAYERDOWNIMGPATH	PATH"chefdown.bmp"	//プレイヤーがレバーを下げているときの画像BMPファイル
#define PLAYERUP			(m_bmpdata[0])			//プレイヤーがレバーを上げているときの画像BMPデータ
#define PLAYERDOWN			(m_bmpdata[1])			//プレイヤーがレバーを下げているときの画像BMPデータ
#define PLAYER_INIT_POSX	(280)					//X座標初期位置
#define PLAYER_INIT_POSY	(2)						//Y座標初期位置			

Player::Player()
{
	m_Conveyor = new Conveyor();
	m_bmpdata = new BitMap[2];//ビットマップデータクラスのメモリを配列確保
	PLAYERUP.LoadBitMap(PLAYERUPIMGPATH);//ビットマップデータクラスに画像をロード
	PLAYERDOWN.LoadBitMap(PLAYERDOWNIMGPATH);//ビットマップデータクラスに画像をロード
	m_position.x = PLAYER_INIT_POSX;//X座標初期化
	m_position.y = PLAYER_INIT_POSY;//Y座標初期化
	m_CtrlPos = 0;//コンベアを動かす位置初期化
}

Player::~Player()
{
	delete[] m_bmpdata;//ビットマップデータクラスのメモリ解放
	m_bmpdata = nullptr;//ビットマップデータクラスのポインタをnullptrに

	delete m_Conveyor;//コンベアクラスのメモリ解放
	m_Conveyor = nullptr;
}


void Player::Init()
{
	m_result = false;//結果表示中フラグをfalseに
}

void Player::InitResult()
{
	m_result = true;//結果表示中フラグをtrueに
}

void Player::Draw()
{
	static char image[3][2] = {
		{4,0},
		{4,4},
		{4,0}
	};//矢印画像
	if (!m_result)
	{//シーンがリザルトじゃないなら
		m_Conveyor->Draw();//コンベアの描画
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 2 * 2; ++x)
			{
				if (x / 2)
					GAME->SetScreen(x / 2 + CONVE_WIDTH + x % 2 + 1,
						y + m_CtrlPos * 16 + CONVE_HIGH_POSY + 6,
						image[y][1 - x % 2]);//右向き矢印
				else
					GAME->SetScreen(x, y + m_CtrlPos * 16 + CONVE_HIGH_POSY + 6, 
						image[y][x % 2]);//左向き矢印
			}
		}
	}
	if (m_Lever)
	{//レバーを動かしているなら
		PLAYERDOWN.OutPutBMP(m_position.x, m_position.y);//レバーを下げているプレイヤーの描画
	}
	else
	{//レバーを動かしていないなら
		PLAYERUP.OutPutBMP(m_position.x, m_position.y);//レバーを下げていないプレイヤーの描画
	}
}

void Player::Update()
{
	if (inport(PK_SP) || inport(PK_SHIFT))
	{//レバーを動かしている状態に変更
		m_Lever = true;
	}
	else
	{//レバー入力判定
		m_Lever = false;
	}
	if (!m_Lever)
	{//レバーを動かしていないなら
		if (inport(PK_UP) || inport(PK_W))
		{//上キーもしくはWキー入力判定
			if (!m_Trigger)
			{//トリガー処理
				m_CtrlPos--;//コンベアそうさ　位置を上に移動
				m_Trigger = true;//トリガーフラグをtrueに
				if (m_CtrlPos < LIMIT_UP)//上側移動制限
					m_CtrlPos = LIMIT_UP;
			}
		}
		else if (inport(PK_DOWN) || inport(PK_S))
		{//下キーもしくはSキー入力判定
			if (!m_Trigger)
			{//トリガー処理
				m_Trigger = true;//トリガーフラグをtrueに
				m_CtrlPos++;//コンベアそうさ　位置を下に移動
				if (m_CtrlPos > LIMIT_DOWN)//下側移動制限
					m_CtrlPos = LIMIT_DOWN;
			}
		}
		else
		{//何も押されていなかったら
			m_Trigger = false;//トリガーフラグをfalseに
		}
	}
	if (m_Lever && !m_result)
	{//コンベアを動かす
		FOODMANAGER->MoveFood(m_CtrlPos,
			m_Conveyor->GetMoveVelo(m_CtrlPos));//コンベアの位置にいる食べ物を動かす
	}
}
