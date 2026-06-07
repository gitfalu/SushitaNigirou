#pragma once
#include "Object.h"
#include "Conveyor.h"


class Player :
    public Object
{
public:
	/// @brief コンストラクタ
	Player(); //コンストラクタ
	/// @brief デストラクタ
	~Player(); //デストラクタ

	/// @brief 初期化
	void Init(); //初期化処理
	/// @brief リザルトシーンよう初期化
	void InitResult(); //結果画面用初期化処理
	/// @brief 描画
	void Draw() override; //描画処理
	/// @brief 更新
	void Update() override; //更新処理

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
    static Player* GetInstance()
	{
		if (s_instance == nullptr)
		{//インスタンスのメモリ確保がまだだったら
			s_instance = new Player();//インスタンスのメモリ確保
		}
		return s_instance;//シングルトンインスタンスを返す
	}
private:
    static Player* s_instance; //シングルトンインスタンス
	Conveyor* m_Conveyor; //コンベアクラスのポインタ
	
	bool m_Lever; //レバーを引いたかどうか
	bool m_Trigger;
	BitMap *m_bmpdata;//ビットマップデータ
	int m_CtrlPos;//コンベアを動かす位置
	bool m_result; //結果表示中かどうか
};
#define PLAYER Player::GetInstance() //シングルトンインスタンスを取得するマクロ
