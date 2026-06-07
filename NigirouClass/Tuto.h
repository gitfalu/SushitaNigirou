#pragma once
#include "Scene.h"
class Tuto :
    public Scene
{
public:
	/// @brief コンストラクタ
	Tuto();
	/// @brief デストラクタ
	~Tuto();
	/// @brief 初期化
	void Init() override;
	/// @brief 更新
	void Update() override;
	/// @brief 描画
	void Draw() override;


private:
};

