#pragma once
#include "Scene.h"
class Nigirou :
    public Scene
{
public:
    /// @brief コンストラクタ
    Nigirou();
    /// @brief デストラクタ
    ~Nigirou();

    /// @brief 初期化
    void Init() override;
    /// @brief 更新
    void Update() override;
    /// @brief 描画
    void Draw() override;

private:
    int m_TimerFrame; //タイマーフレーム数
    int m_Timer; //制限時間
};

