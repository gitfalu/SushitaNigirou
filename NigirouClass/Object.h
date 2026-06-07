#pragma once
#include "system.h"
#include "bitmap.h"

class Object
{
public:
	/// @brief コンストラクタ
	Object();
	/// @brief デストラクタ
	virtual ~Object();
	/// @brief 描画(仮想関数)
	virtual void Draw();
	/// @brief 更新(純粋仮想関数)
	virtual void Update() = 0;
private:
protected:
	typedef struct
	{//座標や移動量をまとめるための構造体
		float x;//X要素
		float y;//Y要素
	}Vec;

	Vec m_position;//位置
	Vec m_OldPosition;//過去の位置
	Vec m_size;//大きさ
	Vec m_velocity;//移動量
};

