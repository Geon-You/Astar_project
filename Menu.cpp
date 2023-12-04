#include "Menu.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Background.h"
#include "Button.h"

void Menu::Initialize()
{
	// �޴� ������ ����� �ؽ��� �ε�
	bmpMap["BackBuffer"] = (new Bitmap)->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["MenuBG"] = (new Bitmap)->LoadBmp(L"Texture/MenuBG.bmp");
	bmpMap["StartBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Start.bmp");
	bmpMap["EditBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Edit.bmp");
	bmpMap["ExitBtn"] = (new Bitmap)->LoadBmp(L"Texture/Button/Exit.bmp");

	// ��� ��ü ���� �� �׸��� Ű ����
	bg = new Background();
	bg->Initialize();
	bg->SetDrawKey("MenuBG");

	// ��ư ��ü ���� �� ��ư ����Ʈ�� ����
	buttons.push_back(Button::CreateButton(200, 400, "StartBtn"));
	buttons.push_back(Button::CreateButton(400, 400, "EditBtn"));
	buttons.push_back(Button::CreateButton(600, 400, "ExitBtn"));

	// �� ��ü�鿡�� bmpMap�� �ּҸ� ����
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
	// ����ۿ� ��� �׸���
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// ����ۿ� ��ư �׸���
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter)
		(*iter)->Render(bmpMap["BackBuffer"]->GetMemDC());

	// ����ۿ� ��ü�� �� �׸� ��, ���������� ���
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
