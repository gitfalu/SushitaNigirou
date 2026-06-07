#pragma once
#include "Object.h"

#define MAX_CONVEYOR (4)


class Conveyor :
    public Object
{
public:
    Conveyor(); //コンストラクタ
    ~Conveyor(); //デストラクタ
    /// @brief 初期化
    void Init(); //初期化処理
    /// @brief 描画
    void Draw() override; //描画処理
    /// @brief 更新
    void Update() override; //更新処理
    /// @brief コンベアの作動速度取得
    /// @param pos 取得するコンベアの番号
    /// @return コンベアの作動速度
    float GetMoveVelo(int pos) ;//コンベアの作動速度取得


private:
    float m_MoveSpeed;//コンベア作動速度
    float m_MoveVec[MAX_CONVEYOR];//コンベア作動方向　右:1　左:-1
    //コンベア描画配列
    const char image[5][7] = {
        {8,8,0,8,8,8,8},
        {8,8,0,0,8,8,8},
        {8,8,0,0,0,8,8},
        {8,8,0,0,8,8,8},
        {8,8,0,8,8,8,8},
    };
}; 


