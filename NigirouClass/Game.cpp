#include "Game.h"
#include "Title.h"


Game* Game::s_instance = nullptr;//シングルトンインスタンス初期化

Game::Game()
{
	m_Scene = nullptr;//シーンポインタ初期化
	m_Scene = new Title();//最初のシーンをタイトルに設定
	//描画画面初期化
	for(int y = 0; y < SCREEN_HEIGHT; ++y)
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{//１フレーム前の画面配列と更新画面配列をすべて黒に設定
			ScreenPrev[y][x] = 32;//１フレーム前の画面配列を黒に設定
			Screen[y][x] = 32;//更新画面配列を黒に設定
		}
}

Game::~Game()
{
	
	//インスタンス削除
	delete m_Scene;//シーンインスタンス削除
	m_Scene = nullptr;
}

void Game::Init()
{
	m_Scene->Init();//シーン初期化
}

void Game::Update()
{
	m_Scene->Update();//現在シーンの更新
}

void Game::Draw()
{
	m_Scene->Draw();//現在シーンの描画
}

bool Game::GameFinish()
{
	if (inport(PK_ESC))
	{//ESCキーが押されたらtrueを返す
		return true;
	}
	return false;
}
