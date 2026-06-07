//bitmap.h
//#pragma once
#ifndef ___BITMAP_H___
#define ___BITMAP_H___

#include "system.h"
#include <iostream>
#include <vector>
using namespace std;

//画像データファイルパス
#define PATH "imgdata/"

class BitMap
{
public:
	/// @brief コンストラクタ
	BitMap();
	/// @brief デストラクタ
	~BitMap();
	/// @brief Bmp画像読み込み
	/// @param szFileName ファイルパス
	void LoadBitMap(const char* szFileName);
	/// @brief　bmp画像出力
	/// @param Posx X座標
	/// @param Posy Y座標
	void OutPutBMP(int Posx,int Posy);

private:
	typedef struct
	{//BMPDATA管理構造体
		vector<unsigned short> bmpData;
		int nWidth;
		int nHeight;

	}BMPDATA;
	BMPDATA *bmpdata;//bmp管理構造体変数
};

#endif // !___BITMAP_H___
