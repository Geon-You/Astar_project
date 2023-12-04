#include "SceneMgr.h"
#include "Scene.h"
#include "Title.h"
#include "Menu.h"
#include "Ingame.h"

// ���� �ʵ� �ʱ�ȭ
SceneMgr* SceneMgr::instance = nullptr;

SceneMgr::SceneMgr()
	: currentScene(nullptr)
{
}

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::SetScene(SceneType type)
{
	// ���� ���� �����Ѵٸ�, �޸� ����
	SafeDelete(currentScene);

	// �Ķ���ͷ� ���� �� Ÿ�Կ� ���� ���� �� ��ü �Ҵ�
	switch (type)
	{
	case SCENE_TITLE:
		currentScene = new Title();
		break;
	case SCENE_MENU:
		currentScene = new Menu();
		break;
	case SCENE_INGAME:
		currentScene = new Ingame();
		break;
	}

	// �� �ʱ�ȭ
	currentScene->Initialize();
}

void SceneMgr::Update()
{
	currentScene->Update();
}

void SceneMgr::Render(HDC hdc)
{
	currentScene->Render(hdc);
}

void SceneMgr::Release()
{
	SafeDelete(currentScene);
}

