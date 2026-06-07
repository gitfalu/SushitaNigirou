#pragma once
#include "bitmap.h"

class Scene
{
public:
	/// @brief コンストラクタ
	Scene();
	/// @brief デストラクタ
	virtual ~Scene();
	/// @brief 初期化
	virtual void Init();
	/// @brief 更新(純粋仮想)
	virtual void Update();
	/// @brief 描画
	virtual void Draw() = 0;
private:

protected:
	BitMap* m_bmpdata;//背景画像bmpdata
};

