#include "MainGame.h"
#include "SceneMgr.h"

void MainGame::Initialize()
{
	srand(GetTickCount64());

	// 전역 윈도우 핸들을 통해 dc를 가져온다
	hdc = GetDC(g_hWnd);

	// 게임 시작 시, 초기 씬 설정
	SceneMgr::GetInstance()->SetScene(SCENE_TITLE);
}

void MainGame::Update()
{
	SceneMgr::GetInstance()->Update();
}

void MainGame::Render()
{
	SceneMgr::GetInstance()->Render(hdc);
}

void MainGame::Release()
{
	// 씬 매니저 싱글 객체 파괴
	SceneMgr::GetInstance()->Destroy();
	// 가져왔던 dc를 시스템에 반환 (해제)
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
