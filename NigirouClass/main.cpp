#include <iostream>
#include "conioex.h"
#include "system.h"
#include "Game.h"
#include "Player.h"
#include "FoodManager.h"
#include "ScoreManager.h"
#include <Windows.h>

#define FPS_LATE (1000/FPS) // 60FPS

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// メモリリークの検出

	int nLastFrameTime, nNowFrameTime,nLastFrameViewTime;// 最終実行フレーム時間, 現在時間, FPS表示用時間
	int nFrameCnt;	// フレームカウント
	int nFPS;// FPS
	unsigned int colorPalette[16] = {
		0x0C0C0C, // 12,12,12
		0xDA3700, // 218,55,0
		0x0EA113, // 14,161,19
		0xDD963A, // 221,150,58
		0x1F0FC5, // 31,15,197
		0x2B66FF, // 43,102,255
		0x009CC1, // 0,156,193
		0xCCCCCC, // 204,204,204
		0x767676, // 118,118,118
		0xFF783B, // 255,120,59
		0x0CC616, // 12,198,22
		0xD6D661, // 214,214,97
		0x5648E7, // 86,72,231
		0x22408E, // 34,64,142
		0xA5F1F9, // 165,241,249
		0xF2F2F2  // 242,242,242
	};

	setpalette(colorPalette);//Colorパレットを更新
	fontsize(10);
	SMALL_RECT sr = { 0, 0, 319, 90 };			// 表示領域を 319x90に設定
	COORD coord = { 320, 91 };					// バッファサイズを320x91に設定
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &sr);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);	//バッファサイズを設定
	SetWindowPos(GetConsoleWindow(), HWND_TOP, 0, 0, 1920, 1080, SWP_SHOWWINDOW);

	GAME->Init();// ゲーム初期化
	timeBeginPeriod(1); // タイマーの精度を1msに設定

	nFrameCnt = 0;// フレームカウント初期化
	nLastFrameTime = nNowFrameTime = nLastFrameViewTime = timeGetTime();// 現在時間取得

	while (!GAME->GameFinish())//ゲームクラスで終了判定をする
	{
		nNowFrameTime = timeGetTime();// 現在時間取得

#ifdef _DEBUG
		if (nNowFrameTime - nLastFrameViewTime >= 500)
		{//0.５秒ごとにFPSを出力
			gotoxy(1, 1);
			nFPS = nFrameCnt * (1000 / (nNowFrameTime - nLastFrameViewTime));//FPSを計算
			std::cout << "FPS:" << nFPS << std::endl;//FPS描画
			nFrameCnt = 0;//フレームカウントリセット
			nLastFrameViewTime = nNowFrameTime;//計測時間を現在の時間に更新
		}
#endif
		if(nNowFrameTime - nLastFrameTime >= FPS_LATE)
		{//最終実行時間から1000/60ミリ秒たっていたら

			GAME->Update();//ゲームの更新処理
			GAME->Draw();//ゲームの描画処理

			GAME->DrawScreen();//スクリーン出力
			
			nLastFrameTime = nNowFrameTime;//最終実行時間を現在時間に更新
			nFrameCnt++;//フレーム数をインクリメント
		}
	}
	PLAYER->DeleteInstance();//プレイヤーのシングルトンインスタンス削除
	FOODMANAGER->DeleteInstance();//食料管理のシングルトンインスタンス削除
	SCOREMANAGER->DeleteInstance();//スコア管理のシングルトンインスタンス削除
	GAME->DeleteInstance();// ゲームインスタンス削除

	setpalette(NULL);

	rewind(stdin);
	getchar();

	return 0;
}