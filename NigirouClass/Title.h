#pragma once
#include "Scene.h"
class Title :
    public Scene
{
public:
    /// @brief コンストラクタ
    Title();
    /// @brief デストラクタ
    ~Title();
    /// @brief 初期化
    void Init() override;
    /// @brief 更新
    void Update() override;
    /// @brief 描画
    void Draw() override;

private:
};

