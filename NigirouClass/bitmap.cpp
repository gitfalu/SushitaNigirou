//読み込めるBMPは
// 
// 24bitBMP
// 
// paintで保存
// 
//BITMAPFILEHEADER：ファイル自体の情報
//BITMAPINFOHEADER：BITMAPの情報
//RGB値が格納
// 
//fopen：ファイル開ける
//fread：ファイルのサイズ分で読み込む
// 
//読み込んだファイルがBMPかを判定
//高さ幅取得→
//INFOOHEADERに格納されてる(biWidth,biHeight)
// 構造体に格納しておく
// vectorのresizeで幅＊高さ
//Vector型：配列のサイズを自由に変えられる (unsigned short)
//一行ずつRGBを格納する場所を作る：unsigned_char*
// 
//一行分のサイズを求める：幅＊３を４の倍数で切り上げ
//メモリ確保：malloc(一行のサイズ)をunsigned_char*(uint8_t*)に入れておく
//vectorが一次元じゃないと使いにくいから幅と高さで位置計算
// 
// 
// freadでメモリ確保したポインタに一行分読み込んで格納
// 読み込んでずらす用のポインタも用意しておくと後々楽
//RGB値を格納する変数を作って格納(0から15の値にするためにRGB値を格納しておく（conioex使うならこっちの方がいい）)
// 
// 
//  色情報用の変数をunsignedintでつくる
// 色を変換するためにRGB(R,G,B)；を使う
// BMPファイルの値位置を補正するためにYだけ逆順で読み込む
// 行数分for
// 一画素ごとに16色と比較して色番号を探す
// 一致している色がみつかったらbreak;
// vectorの先頭アドレスを.data()で取得する
// 位置計算をして
// 計算した位置に探した色番号を格納
// コンソールの色情報を配列に格納しておけばCONSOLE_SCREEN_BUFFER_INFO(EX)を使わなくていい
// 色なかったら透明色(または背景と同じ色)を格納
// 
//********************* 
// fclose();
//
// メモリ開放：free();
// ********************
// 
// 
// 
// vector格納時の計算式を利用しつつ出力
// 
// 計算時は保存先の幅を使う
//



#include "Game.h"
#include "bitmap.h"


#define FILE_TYPE (0x4D42)			//"BM"をリトルエンディアンで解釈した値
#define FILE_HEADER_SIZE (14)		//BMPファイルヘッダサイズ
#define INFO_HEADER_SIZE (40)		//Windowsヘッダサイズ
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)	//標準のヘッダサイズ
#define COLOR_BITCOUNT (24)			//色情報に使用するビット数

#define MAX_COLOR (16)				//最大色数

BitMap::BitMap()
{
	bmpdata = new BMPDATA();//ビットマップデータ構造体のメモリ確保
	bmpdata->nHeight = 0;//高さの初期化
	bmpdata->nWidth = 0;//幅の初期化
}

BitMap::~BitMap()
{
	delete bmpdata;//ビットマップデータクラスのメモリ解放
	bmpdata = nullptr;//ビットマップデータクラスのポインタをnullptrに
}

void BitMap::LoadBitMap(const char* szFileName)
{
	unsigned int g_currentPalette[MAX_COLOR];	//現在のパレットデータ
	//----- 変数宣言 -----
	FILE* fp;												//イラストデータのファイルポインタ
	BITMAPFILEHEADER fileHeader;							//BMP_FILE_HEADER領域の先頭アドレス
	BITMAPINFOHEADER infoHeader;							//BMP_INFO_HEADER領域の先頭アドレス
	//unsigned __int8 uHeaderBuffer[DEFAULT_HEADER_SIZE];		//読み込み先
	int nLength;											//一行の長さ
	uint8_t* readPointer;									//読み込み位置
	uint8_t* bufferPointer;									//読み込み行
	unsigned int uColor;									//色情報
	int nRed;												//RGBのR
	int nGreen;												//RGBのG
	int nBlue;												//RGBのB
	//ファイルを開く
	fp = fopen(szFileName, "r");
	if (fp == NULL)
	{
		printf("%sが見つかりませんでした。", szFileName);
		exit(EXIT_FAILURE);
	}

	//----- 初期化処理 -----
	getpalette(g_currentPalette);//カラーパレットの取得
	uColor = 0x00000000;//色情報の初期化


	fread(&fileHeader, sizeof(fileHeader), 1, fp);//ファイルヘッダの読み込み
	fread(&infoHeader, sizeof(infoHeader), 1, fp);//情報ヘッダの読み込み


	bmpdata->nHeight = infoHeader.biHeight;//高さの取得
	bmpdata->nWidth = infoHeader.biWidth;//幅の取得
	
	bmpdata->bmpData.resize(infoHeader.biWidth * infoHeader.biHeight);//ビットマップデータのメモリ確保


	//ファイルのフォーマットチェック
	if (fileHeader.bfOffBits != DEFAULT_HEADER_SIZE ||
		infoHeader.biBitCount != COLOR_BITCOUNT ||
		infoHeader.biHeight <= 0)
	{//読み取れない形式だったら
		printf("%sが読み取れない形式です。", szFileName);
		exit(EXIT_FAILURE);
	}

	//一行のサイズを求める(切り上げ)
	nLength = (infoHeader.biWidth * 3 + 3) / 4 * 4; //infoHeader.biWidth * 3 + infoHeader.biWidth % 4;

	bufferPointer = (uint8_t*)malloc(nLength);//一行分のメモリ確保
	//メモリ確保
	if (bufferPointer == NULL)
	{//バッファポインタがNULLだったら
		printf("%sの読み取り中にメモリが確保出来ませんでした。", szFileName);
		exit(EXIT_FAILURE);
	}

	for (int y = infoHeader.biHeight - 1; y >= 0; y--)
	{
		//一行単位で読み込む
		if (fread(bufferPointer, nLength, 1, fp) == false)
		{
			printf("%sが読み取れませんでした。", szFileName);
			exit(EXIT_FAILURE);
		}

		//読み込み位置を設定
		readPointer = bufferPointer;

		//一画素単位で読み込む
		for (int x = 0; x < infoHeader.biWidth; x++)
		{
			//RGB値を読み込む
			nBlue = *readPointer++;//Bの読み込みアドレスを一つ進める
			nGreen = *readPointer++;//Gの読み込みアドレスを一つ進める
			nRed = *readPointer++;//Rの読み込みアドレスを一つ進める

			//RGB値から色を作成
			uColor = RGB(nRed, nGreen, nBlue);

			//対応するパレット番号を探して記録
			for (int i = 0; i < MAX_COLOR; i++)
			{
				if (uColor == g_currentPalette[i])
				{//パレットと一致する色の場合
					*(bmpdata->bmpData.data() + y * infoHeader.biWidth + x) = i;//bmpdataに色を設定
					break;
				}

				if (i == MAX_COLOR - 1)
				{//一致する色がなかったら
					*(bmpdata->bmpData.data() + y * infoHeader.biWidth + x) = 32;//bmpdataに32を設定
				}
			}
		}
	}

	//メモリ解放
	free(bufferPointer);

	//ファイルを閉じる
	fclose(fp);
}
void BitMap::OutPutBMP(int Posx, int Posy)
{
	int y, x;
	for (y = 0; y < bmpdata->nHeight; ++y)
	{
		for (x = 0; x < bmpdata->nWidth; ++x)
		{
			if (*(bmpdata->bmpData.data() + y * bmpdata->nWidth + x) == 32)
			{//bmpdataが32の時
				continue;//描画処理をしない
			}
			GAME->SetScreen(Posx + x,Posy + y, 
				*(bmpdata->bmpData.data() + y * bmpdata->nWidth + x));//色データを設定
		}
	}
}