#include "SceneMgr.h"
#include "Scene.h"
#include "Title.h"
#include "Menu.h"
#include "Ingame.h"

// 정적 필드 초기화
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
	// 이전 씬이 존재한다면, 메모리 해제
	SafeDelete(currentScene);

	// 파라미터로 받은 씬 타입에 따른 실제 씬 객체 할당
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

	// 씬 초기화
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

