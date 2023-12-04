#include "Menu.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Background.h"
#include "Button.h"

void Menu::Initialize()
{
	// 메뉴 씬에서 사용할 텍스쳐 로드
	bmpMap["BackBuffer"] = (new Bitmap)->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["MenuBG"] = (new Bitmap)->LoadBmp(L"Texture/MenuBG.bmp");
	bmpMap["StartBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Start.bmp");
	bmpMap["EditBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Edit.bmp");
	bmpMap["ExitBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Exit.bmp");

	// 배경 객체 생성 및 그리기 키 설정
	bg = new Background();
	bg->Initialize();
	bg->SetDrawKey("MenuBG");

	// 버튼 객체 생성 후 버튼 리스트에 삽입
	buttons.push_back(Button::CreateButton(200, 400, "StartBtn"));
	buttons.push_back(Button::CreateButton(400, 400, "EditBtn"));
	buttons.push_back(Button::CreateButton(600, 400, "ExitBtn"));

	// 씬 객체들에게 bmpMap의 주소를 전달
	Object::SetBmpMap(&bmpMap);
}

void Menu::Update()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter)
	{
		auto type = (*iter)->Update();

		if (type > SCENE_NONE)
		{
			SceneMgr::GetInstance()->SetScene(type);
			return;
		}
	}
}

void Menu::Render(HDC hdc)
{
	// 백버퍼에 배경 그리기
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 백버퍼에 버튼 그리기
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter)
		(*iter)->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 백버퍼에 객체들 다 그린 후, 최종적으로 출력
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, 
		bmpMap["BackBuffer"]->GetMemDC(), 0, 0, SRCCOPY);
}

void Menu::Release()
{
	SafeDelete(bg);

	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter)
		SafeDelete(*iter);

	buttons.clear();
}

Menu::Menu()
{
}

Menu::~Menu()
{
	Release();
}
