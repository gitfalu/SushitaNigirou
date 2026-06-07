#pragma once
#include "Object.h"

class Spice :
    public Object
{
public:
	/// @brief コンストラクタ
	Spice();
	/// @brief デストラクタ
	~Spice();
	/// @brief 初期化
	void Init(); //初期化処理
	/// @brief 描画
	void Draw() override;
	/// @brief 更新
	void Update() override;

private:
	typedef enum//スパイスの種類
	{
		SUGAR = 0,
		SALT,
		VINEGAR,
		SOYSAUCE,
		MISO,
		SUGARSOY,
		VINESOY
	}SPICE;

};

