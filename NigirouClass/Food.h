#pragma once
#include "Object.h"

class Food :
    public Object
{
public:
	/// @brief コンストラクタ
	Food();
	/// @brief デストラクタ
	~Food();
	/// @brief 初期化
	void Init(); //初期化処理
	/// @brief 描画
	void Draw() override;//描画処理
	/// @brief 更新
	void Update() override;//更新処理
	/// @brief 食べ物の生成
	/// @param FoodType 食べ物の種類
	/// @param bmpdata 食べ物の種類に応じたbmpdata
	void Create(int FoodType,BitMap* bmpdata);//食べ物の生成
	/// @brief 食べ物の種類を取得
	/// @return 食べ物の種類
	int GetFoodType() { return m_foodType; };//食べ物の種類取得
	/// @brief スパイスに当たったかどうか判定する
	/// @return スパイスにあたっていたらtrue　そうでなければfalse
	bool CollisionSpice();//スパイスとの当たり判定
	/// @brief 使用しているか取得
	/// @return 使用していればtrue　使用していなければfalse
	bool GetUse() { return m_bUse; };//使用中かどうか
	/// @brief スコアの値を取得
	/// @return スコアの値
	int GetScoreValue() { return m_ScoreValue; };//スコア値取得
	/// @brief 食べ物を移動させる
	/// @param ConvePos 作動させるコンベアの位置
	/// @param MoveVelo 移動する速度
	void MoveFood(int ConvePos,float MoveVelo);//食べ物の移動
private:
	BitMap *m_bmpdata;//ビットマップデータ
	int m_foodType; //食べ物の種類
	int m_ConvePos; //コンベアの位置
	int m_ScoreValue; //食べ物のスコア
	bool m_bUse; //使用中かどうか
};

