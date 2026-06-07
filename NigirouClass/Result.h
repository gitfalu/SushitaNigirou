#pragma once
#include "Scene.h"

class Result:
	public Scene
{
public:
	/// @brief コンストラクタ
	Result();
	/// @brief デストラクタ
	~Result();
	/// @brief 初期化
	void Init() override;
	/// @brief 更新
	void Update() override;
	/// @brief 描画
	void Draw() override;

private:

};

