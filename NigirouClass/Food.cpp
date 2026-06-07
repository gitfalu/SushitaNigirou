#include "Food.h"
#include "system.h"

#define DOWN_SPEED	(0.1f)			//食べ物の落下速度
#define INIT_Y		(2.0f)			//食べ物の初期Y座標
#define LIMIT_LEFT	(3)				//画面左限
#define LIMIT_RIGHT (CONVE_WIDTH)	//画面右限
#define LIMIT_DOWN	(80)			//画面下限
#define SPICE_Y		(70)			//スパイスのY座標
#define SPICE_X		(6)				//スパイスのX座標
#define SPICE_R		(4)				//スパイスの半径
#define SPICE_SIZE	(8)				//スパイスのサイズ
#define FOOD_SIZE	(16.0f)			//食べ物のサイズ
#define Collision_Correction (3.0f)	//当たり判定補正

Food::Food()
{
	//ビットマップデータクラスのメモリ確保
	m_ConvePos = 0;//コンベアの位置初期化
	m_bUse = false;//使用してないに設定
	m_size.x = FOOD_SIZE;//食べ物の幅設定
	m_size.y = FOOD_SIZE;//食べ物の高さ設定
	m_position.x = 0.0f;//初期X座標設定
	m_position.y = INIT_Y;//初期Y座標設定
	m_foodType = 0;//食べ物の種類初期化
	m_ScoreValue = 0;//スコア初期化

	//m_bmpdataはメモリリークの恐れがあるためManagerから直接受け取る
}

Food::~Food()
{
	
}

void Food::Init()
{
	m_ConvePos = 0;//コンベアの位置初期化
	m_position.y = INIT_Y;//初期Y座標設定
	m_bUse = false;//使用中に設定
}

void Food::Draw()
{
	m_bmpdata->OutPutBMP(m_position.x, m_position.y);//食べ物の描画
}

void Food::Update()
{
	m_position.y += DOWN_SPEED;//Y座標を下に移動
	m_ConvePos = 
		(m_position.y + m_size.y / 2 - CONVE_HIGH_POSY) / 16;//コンベアの位置を更新
	if (m_position.y + m_size.y / 2 > LIMIT_DOWN  ||
		m_position.x + m_size.x / 2 > LIMIT_RIGHT ||
		m_position.x + m_size.x / 2 < LIMIT_LEFT)
	{//範囲外に出たらオブジェクトを使用してないに設定
		m_bUse = false;
	}
}

void Food::Create(int FoodType,BitMap* bmpdata)
{
	int RandStack = rand() % FOODTYPE;//乱数取得
	m_ConvePos = 0;//コンベアの位置初期化
	m_position.x = RandStack * m_size.x + 4;//X座標をランダムに設定
	m_position.y = INIT_Y;//初期Y座標設定
	m_foodType = FoodType;//食べ物の種類を設定
	m_bmpdata = bmpdata;//ビットマップデータを設定
	m_bUse = true;//使用中に設定
	if (m_foodType < RandStack)//初期位置より目標位置が左(値が小さい)の場合
	{//スコア計算
		m_ScoreValue = RandStack - m_foodType + 1;//スコアを設定

	}
	else//初期位置より目標位置が右(値が大きい)の場合
	{
		m_ScoreValue = m_foodType - RandStack + 1;//スコアを設定
	}
}

bool Food::CollisionSpice()
{
	Vec FoodCenter = { m_position.x + (m_size.x / 2),
		m_position.y + (m_size.y /2)};//Foodの中心座標
	Vec SpiceCenter = { (m_foodType * (SPICE_SIZE * 2)) + SPICE_SIZE + SPICE_X,
		SPICE_Y + SPICE_R };//Spiceの中心座標

	//FoodとSpiceの中心間の距離
	float dist =(FoodCenter.x - SpiceCenter.x) * (FoodCenter.x - SpiceCenter.x) +//X距離の2乗
			(FoodCenter.y - SpiceCenter.y) * (FoodCenter.y - SpiceCenter.y);//Y距離の2乗

	if (dist < (SPICE_R + 2) * (SPICE_R + 2))//距離の2乗が半径+接触判定補正の和の2乗より小さい
	{//当たった
		m_bUse = false;//使用してないに設定
		return true;//当たったことを返す
	}
	return false;//当たらなかったことを返す
}

void Food::MoveFood(int ConvePos,float MoveVelo)
{
	if (m_ConvePos == ConvePos)
	{//操作するコンベアの位置と現在いるコンベアの位置が同じ場合
		m_position.x += MoveVelo;//食べ物を移動
	}
}
