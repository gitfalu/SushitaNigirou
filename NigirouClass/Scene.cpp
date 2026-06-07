#include "Scene.h"

Scene::Scene()
{
	m_bmpdata = new BitMap();//ビットマップクラスのインスタンスを生成
}

Scene::~Scene()
{
	delete m_bmpdata;//ビットマップクラスのインスタンスを破棄
	m_bmpdata = nullptr;
}

void Scene::Init()
{
}

void Scene::Update()
{
}
