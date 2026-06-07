#include "ScoreManager.h"

ScoreManager* ScoreManager::s_instance = nullptr;//シングルトンインスタンスの初期化

#define COMPLETED_HIGHT		(20)		//獲得した食べ物の表示高さ
#define COMPLETED_WIDTH		(20)		//獲得した食べ物の表示幅
#define COMPLETED_INIT_X	(280)		//獲得した食べ物の画像のX座標
#define FOOD_HIGHT			(16)		//獲得した食べ物の画像の高さ
#define TIMER_UP			(3)			//タイマーの上昇量


#define SUGAPAN			PATH"sugapan.bmp"		//ラスク
#define SALTSUIKA		PATH"saltsuika.bmp"		//塩スイカ
#define VINESARAD		PATH"vinesarad.bmp"		//ドレッシングサラダ
#define SOYSUSHI		PATH"soysushi.bmp"		//寿司と醤油
#define MISOKATU		PATH"misokatu.bmp"		//味噌カツ
#define SUGASOYMOTI		PATH"sugasoymoti.bmp"	//醤油餅	
#define VINESOYGYOZA	PATH"vinesoygyoza.bmp"	//酢醤油餃子

//*******************************************************************
// 
// この下Completedクラス
// 
// 獲得した食べ物を表示・更新するクラス
// 
//*******************************************************************

Completed::Completed()
{
	m_Score = new Score();//獲得した食べ物の数を表示するクラスの生成
}

Completed::~Completed()
{
	delete m_Score;//獲得した食べ物の数を表示するクラスの解放
	m_Score = nullptr;
}
/// @brief	獲得した食べ物を表示するクラスの初期化
/// @param bitMap ビットマップデータをManagerから受け取る
/// @param x 描画位置のx座標
/// @param y 描画位置のy座標
void Completed::Init(BitMap* bitMap, float x, float y)
{
	m_BitMap = bitMap;//食べ物の画像の設定
	m_position.x = x;//食べ物の表示位置の設定
	m_position.y = y;//食べ物の表示位置の設定
	m_Score->SetLimit(999, m_position.x,m_position.y + FOOD_HIGHT - 3.0f);//獲得した食べ物の数の最大値設定
}

void Completed::Update()
{

}
/// @brief 獲得した食べ物の数と画像の描画
void Completed::Draw()
{
	m_BitMap->OutPutBMP(m_position.x, m_position.y);//食べ物の画像の描画
	m_Score->Draw();//獲得した食べ物の数の描画
}
/// @brief 獲得した食べ物の数を増やす
void Completed::AddGetFood()
{
	m_Score->AddScore(1);//獲得した食べ物の数を増やす
}
/// @brief 獲得した食べ物の数をリセット
void Completed::ScoreReset()
{
	m_Score->ScoreReset();//獲得した食べ物の数をリセット
}


//******************************************************************
// 
// この下ScoreManagerクラス
// 
// スコアの管理をするクラス
// 
//******************************************************************

ScoreManager::ScoreManager()
{
	m_timerCntUp = 0;//タイマー上昇量初期化
	m_position = new Vec();//食べ物の表示位置の生成
	m_result = false;
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_Completed[i] = new Completed();//獲得した食べ物を表示するクラスの生成
		m_BitMap[i] = new BitMap();//獲得した食べ物を表示するクラスの生成
	}
	m_Score = new Score();//総合スコア用クラスの生成
	m_Score->SetLimit(99999999, 5.0f, 5.0f);//スコアの最大値設定
	//食べ物の画像の読み込み
	m_BitMap[0]->LoadBitMap(SUGAPAN);//ラスクの画像を読み込む
	m_BitMap[1]->LoadBitMap(SALTSUIKA);//塩スイカの画像を読み込む
	m_BitMap[2]->LoadBitMap(VINESARAD);//ドレッシングサラダの画像を読み込む
	m_BitMap[3]->LoadBitMap(SOYSUSHI);//寿司と醤油の画像を読み込む
	m_BitMap[4]->LoadBitMap(MISOKATU);//味噌カツの画像を読み込む
	m_BitMap[5]->LoadBitMap(SUGASOYMOTI);//醤油餅の画像を読み込む
	m_BitMap[6]->LoadBitMap(VINESOYGYOZA);//酢醤油餃子の画像を読み込む
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_Completed[i]->Init(m_BitMap[i],
			(i + 1) % 2 * COMPLETED_WIDTH + COMPLETED_INIT_X,
			((i + 1) / 2) * COMPLETED_HIGHT);//獲得した食べ物を表示するクラスの初期化
	}
}

ScoreManager::~ScoreManager()
{
	for (int i = 0; i < FOODTYPE; ++i)
	{
		delete m_Completed[i];//獲得した食べ物を表示するクラスの解放
		m_Completed[i] = nullptr;
		delete m_BitMap[i];//獲得した食べ物を表示するクラスの解放
		m_BitMap[i] = nullptr;
	}
	delete m_Score;//総合スコア用クラスの解放
	m_Score = nullptr;
	delete m_position;//食べ物の表示位置の解放
	m_position = nullptr;
}

void ScoreManager::Init()
{
	m_position->x = 5.0f;//食べ物の表示位置の初期化
	m_position->y = 5.0f;//食べ物の表示位置の初期化
	m_timerCntUp = 0;//タイマー上昇量初期化
	for (int i = 0; i < FOODTYPE; ++i)
	{
		if (m_result)
		{
			m_Completed[i]->Init(m_BitMap[i],
				i * COMPLETED_WIDTH,
				COMPLETED_HIGHT + 10.0f);//獲得した食べ物を表示するクラスの初期化
		}
		else
		{
			m_Score->ScoreReset();//総合スコアリセット
			m_Completed[i]->ScoreReset();//獲得した食べ物の数をリセット
			m_Completed[i]->Init(m_BitMap[i], 
				(i + 1) % 2 * COMPLETED_WIDTH + COMPLETED_INIT_X,
				((i + 1) / 2)* COMPLETED_HIGHT);//獲得した食べ物を表示するクラスの初期化
		}
	}
}

void ScoreManager::Update()
{
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_Completed[i]->Update();//獲得した食べ物の数を更新
	}
}

void ScoreManager::Draw()
{
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_Completed[i]->Draw();//獲得した食べ物の数を表示
	}
	if (m_result)
	{
		m_Score->Draw();//スコアの表示
	}
}

void ScoreManager::AddGet(int FoodType)
{
	m_Completed[FoodType]->AddGetFood();//獲得した食べ物の数を増やす
	m_timerCntUp = TIMER_UP;//タイマーの上昇量を設定
}

void ScoreManager::AddScore(int AddScore)
{
	m_Score->AddScore(AddScore);//スコアを増やす
}