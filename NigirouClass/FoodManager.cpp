#include "FoodManager.h"
#include "ScoreManager.h"
FoodManager* FoodManager::s_instance = nullptr;//シングルトンインスタンス初期化


#define BREADPATH	PATH"bread.bmp"		//パン画像
#define SUIKAPATH	PATH"suika.bmp"		//スイカ画像	
#define SARADPATH	PATH"sarad.bmp"		//サラダ画像
#define SUSHIPATH	PATH"sushi.bmp"		//寿司画像
#define KATUPATH	PATH"katu.bmp"		//カツ画像
#define MOTIPATH	PATH"moti.bmp"		//餅画像
#define GYOZAPATH	PATH"gyoza.bmp"		//餃子画像

FoodManager::FoodManager()
{
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		m_pFood[i] = new Food();//食料クラスのメモリを配列確保

	}
	m_CreateFrameCnt = 0;//生成用フレームカウント初期化
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_bmpdata[i] = new BitMap();//BMPデータクラスのメモリを配列確保
	}
	m_pSpice = new Spice();//スパイスオブジェクトの生成
	//食料の画像データを読み込み
	m_bmpdata[0]->LoadBitMap(BREADPATH);//パン
	m_bmpdata[1]->LoadBitMap(SUIKAPATH);//スイカ
	m_bmpdata[2]->LoadBitMap(SARADPATH);//サラダ
	m_bmpdata[3]->LoadBitMap(SUSHIPATH);//寿司
	m_bmpdata[4]->LoadBitMap(KATUPATH);//カツ
	m_bmpdata[5]->LoadBitMap(MOTIPATH);//餅
	m_bmpdata[6]->LoadBitMap(GYOZAPATH);//餃子
}

FoodManager::~FoodManager()
{
	for (int i = 0; i < FOODTYPE; ++i)
	{
		delete m_bmpdata[i];//ビットマップデータクラスのメモリ解放
		m_bmpdata[i] = nullptr;//ビットマップデータクラスのポインタをnullptrに
	}
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		delete m_pFood[i];//食料クラスのメモリ解放
		m_pFood[i] = nullptr;//食料クラスのポインタをnullptrに
	}
	delete m_pSpice;//スパイスオブジェクトの解放
	m_pSpice = nullptr;//スパイスオブジェクトのポインタをnullptrに
}

void FoodManager::Init()
{
	srand(time(NULL));//乱数の種を初期化
	m_CreateFrameCnt = 0;//生成用フレームカウント初期化
	for (int i = 0; i < FOODTYPE; ++i)
	{
		m_pFood[i]->Init();//食料の初期化
	}
}

void FoodManager::Update()
{
	++m_CreateFrameCnt;//生成用フレームカウントをインクリメント
	if (m_CreateFrameCnt > 90)//60フレームごとに食料生成
	{
		Create();//食料生成処理
		m_CreateFrameCnt = 0;//フレームカウントをリセット
	}
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		if (!m_pFood[i]->GetUse())continue;//使用中でなければスルー
		m_pFood[i]->Update();//食料の更新
	}
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		if(!m_pFood[i]->GetUse())continue;//使用中でなければスルー
		if (m_pFood[i]->CollisionSpice())//スパイスと食べ物の接触判定
		{
			SCOREMANAGER->AddGet(m_pFood[i]->GetFoodType());//獲得した食料の種類をスコアマネージャーに通知
			SCOREMANAGER->AddScore(m_pFood[i]->GetScoreValue());//スコアマネージャーにスコアを加算
		}
	}
}

void FoodManager::Draw()
{
	m_pSpice->Draw();//スパイスの描画
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		if (!m_pFood[i]->GetUse())continue;//使用中でなければスルー
		m_pFood[i]->Draw();//食料の描画
	}
}

void FoodManager::Create()
{
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		if (m_pFood[i]->GetUse())continue;//使用中ならスルー
	
		int type = rand() % FOODTYPE;//食料の種類をランダムに決定
		m_pFood[i]->Create(type, m_bmpdata[type]);//食料の初期化
		break;
	}
}

void FoodManager::MoveFood(int ConvePos,float Movevelo)
{
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		if(!m_pFood[i]->GetUse())continue;//使用中でなければスルー
		m_pFood[i]->MoveFood(ConvePos,Movevelo);//食べ物の移動
	}
}
