#include "MainGame.h"
#include "SceneMgr.h"

void MainGame::Initialize()
{
	srand(GetTickCount64());

	// ���� ������ �ڵ��� ���� dc�� �����´�
	hdc = GetDC(g_hWnd);

	// ���� ���� ��, �ʱ� �� ����
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
	// �� �Ŵ��� �̱� ��ü �ı�
	SceneMgr::GetInstance()->Destroy();
	// �����Դ� dc�� �ý��ۿ� ��ȯ (����)
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
