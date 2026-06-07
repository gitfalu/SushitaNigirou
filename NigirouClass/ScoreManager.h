#pragma once
#include "Object.h"
#include "Score.h"

class Completed :
    public Object
{
public:
	/// @brief コンストラクタ
	Completed();
	/// @brief デストラクタ
	~Completed();
	/// @brief 初期化
	/// @param bitMap 画像読み込み済みbmpdata
	/// @param x 描画X座標
	/// @param y 描画Y座標
	void Init(BitMap* bitMap, float x, float y);//初期化
	/// @brief 更新
	void Update() override;
	/// @brief 描画
	void Draw() override;
	/// @brief 食べ物取得
	void AddGetFood();
	/// @brief 取得した食べ物のリセット
	void ScoreReset();//獲得した食べ物の数をリセット
private:
	BitMap* m_BitMap;//食べ物の画像
	Score* m_Score;//獲得した食べ物の数を表示するクラス
};

class ScoreManager
{
public:
	/// @brief コンストラクタ
	ScoreManager();//コンストラクタ
	/// @brief デストラクタ
	~ScoreManager();//デストラクタ
	/// @brief シングルトンインスタンス取得
	/// @return シングルトンインスタンス
	static ScoreManager* GetInstance()
	{
		if (s_instance == nullptr)
		{//インスタンスがnullptrだったら
			s_instance = new ScoreManager();//インスタンスのメモリ確保
		}
		return s_instance;//シングルトンインスタンスを返す
	}
	/// @brief シングルトンインスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;//インスタンスのメモリ解放
			s_instance = nullptr;
		}
	}
	/// @brief 初期化
	void Init();//スコアの初期化
	/// @brief Nigirouシーン用に変更
	void Nigirou()
	{
		m_result = false;
	}
	/// @brief リザルトシーンように変更
	void Result()
	{
		m_result = true; 
	}//リザルトシーンを描画できる設定にする
	/// @brief 更新
	void Update();//スコアの更新
	/// @brief 描画
	void Draw();//スコアの描画
	/// @brief 獲得した食べ物の取得個数を増やす
	/// @param FoodType 食べ物の種類
	void AddGet(int FoodType);//獲得した食べ物の数を増やす
	/// @brief スコアを増やす
	/// @param AddScore スコアの上昇量
	void AddScore(int AddScore);//スコアを増やす
	/// @brief タイマーの値を増やす量を取得する
	/// @return タイマーのカウントを増やす量(int)
	int TimerCntUp()
	{
		int timerUpStack = m_timerCntUp;//タイマーの増加量を保管
		m_timerCntUp = 0;//タイマーの増加量をリセット
		return timerUpStack;//タイマーの増加量
	}

private:
	struct Vec
	{//座標や移動量をまとめるための構造体
		float x;//X要素
		float y;//Y要素
	};
	static ScoreManager *s_instance;	//シングルトンインスタンス
	Completed* m_Completed[FOODTYPE];	//獲得した食べ物を表示するクラス
	BitMap* m_BitMap[FOODTYPE];			//食べ物の画像
	Score* m_Score;						//総合スコア用クラス
	Vec* m_position;					//食べ物の表示位置
	bool m_result;						//リザルトシーンを描画するかどうか
	int m_timerCntUp;					//タイマーのカウントを回復する値
};
#define SCOREMANAGER ScoreManager::GetInstance()//シングルトンインスタンス取得



