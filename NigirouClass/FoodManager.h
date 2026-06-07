#pragma once
#include "Food.h"
#include "bitmap.h"
#include "system.h"
#include "Spice.h"

#define MAX_FOOD (20)	//最大食べ物数

class FoodManager
{
public:
	/// @brief コンストラクタ
	FoodManager();
	/// @brief デストラクタ
	~FoodManager();

	/// @brief 初期化
	void Init();
	/// @brief 更新
	void Update();
	/// @brief 描画
	void Draw();
	/// @brief 食べ物生成
	void Create();//食料生成
	/// @brief 食べ物移動
	/// @param ConvePos 移動箇所
	/// @param MoveVelo 移動量
	void MoveFood(int ConvePos,float MoveVelo);//食料移動
	/// @brief シングルトンインスタンス削除
	void DeleteInstance() //シングルトンインスタンスの削除
	{
		if (s_instance != nullptr)
		{
			delete s_instance;//インスタンスの削除
			s_instance = nullptr;//ポインタをnullptrに
		}
	}
	/// @brief シングルトンインスタンス取得
	/// @return シングルトンインスタンス
	static FoodManager* GetInstance()
	{
		if (s_instance == nullptr)
		{//インスタンスがnullptrだったら
			s_instance = new FoodManager();//インスタンスのメモリ確保
		}
		return s_instance;//シングルトンインスタンスを返す
	}

private:
	static FoodManager* s_instance;//シングルトンインスタンス
	Food* m_pFood[MAX_FOOD];//食べ物を複数管理する配列
	Spice* m_pSpice;//スパイスオブジェクト
	BitMap *m_bmpdata[FOODTYPE];//ビットマップデータ

	int m_CreateFrameCnt;//生成用フレームカウント
};
#define FOODMANAGER FoodManager::GetInstance() //シングルトンインスタンスを取得するマクロ