#pragma once
#include "Scene.h"
#include "system.h"

class Game
{
public:
	/// @brief コンストラクタ
	Game();
	/// @brief デストラクタ
	~Game();

	/// @brief 初期化
	void Init();//初期化
	/// @brief 更新
	void Update();//更新
	/// @brief 描画
	void Draw();//描画
	/// @brief ゲーム終了判定
	/// @return escキーを押したときtrueを返す
	bool GameFinish();//ゲーム終了判定
	/// @brief シングルトンインスタンスを削除
	void DeleteInstance()//シングルトンインスタンス削除
	{
		if (s_instance != nullptr)
		{
			delete s_instance;//インスタンスのメモリ解放
			s_instance = nullptr;
		}
	}
	/// @brief シーン変更
	/// @param scenedata 何のシーンに移行するかをnewで指定
	void ChangeScene(Scene* scenedata)//シーン変更
	{
		delete m_Scene;//元のシーンのメモリを解放
		m_Scene = nullptr;
		m_Scene = scenedata;//変更先のシーンを入れる
	}
	/// @brief シングルトンインスタンスを取得
	/// @return シングルトンインスタンス
	static Game* GetInstance()//シングルトンインスタンス取得
	{
		if(s_instance == nullptr)
		{//インスタンスがnullptrだったら
			s_instance = new Game();//インスタンスのメモリ確保
		}
		return s_instance;//シングルトンインスタンスを返す
	}
	/// @brief スクリーン配列に色を指定
	/// @param x 表示X座標
	/// @param y 表示Y座標
	/// @param color 表示色
	void SetScreen(int x, int y, int color)
	{
		Screen[y][x] = color;//指定した座標に色を代入
	}
	/// @brief 画面描画
	void DrawScreen()
	{
		for (int y = 0; y < SCREEN_HEIGHT; ++y)
		{
			for (int x = 0; x < SCREEN_WIDTH; ++x)
			{
				if (ScreenPrev[y][x] == Screen[y][x])
				{//１フレーム前と同じ色なら
					Screen[y][x] = BLACK;//現在のスクリーンを初期化し
					continue;//再実行
				}
				ScreenPrev[y][x] = Screen[y][x];//プレビュー配列に現在の値を保管
				textattr(Screen[y][x] << 4);//背景色に指定
				gotoxy(x * 2 + 1, y);//座標を移動
				//空白を二つ置く
				putchar(' ');
				putchar(' ');
				Screen[y][x] = BLACK;//現在背景を初期化
			}
		}
		textattr(WHITE);//背景色を元に戻す
	}
private:
	static Game* s_instance;//シングルトンインスタンス
	Scene* m_Scene;//シーンインスタンス

	//前フレーム比較用描画画面
	char ScreenPrev[SCREEN_HEIGHT][SCREEN_WIDTH];
	//描画画面
	char Screen[SCREEN_HEIGHT][SCREEN_WIDTH];
	
};

#define GAME (Game::GetInstance())//シングルトンインスタンス取得マクロ

