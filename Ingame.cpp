#include "Ingame.h"
#include "AbstractFactory.h"
#include "TileBackground.h"
#include "Player.h"

void Ingame::Initialize()
{
	bmpMap["BackBuffer"] = (new Bitmap)->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["Tile"] = (new Bitmap)->LoadBmp(L"Texture/Tile.bmp");

	bmpMap["Player_DOWN"] = (new Bitmap)->LoadBmp(L"Texture/Player/Player_DOWN.bmp");
	bmpMap["Player_UP"] = (new Bitmap)->LoadBmp(L"Texture/Player/Player_UP.bmp");
	bmpMap["Player_LEFT"] = (new Bitmap)->LoadBmp(L"Texture/Player/Player_LEFT.bmp");
	bmpMap["Player_RIGHT"] = (new Bitmap)->LoadBmp(L"Texture/Player/Player_RIGHT.bmp");

	bg = AbstractFactory<TileBackground>::CreateObject();

	objList[OBJ_PLAYER].push_back(AbstractFactory<Player>::CreateObject());

	Object::SetBmpMap(&bmpMap);
}

void Ingame::Update()
{
	// ��ü ����Ʈ ������ŭ �ݺ�
	for (int i = 0; i < OBJ_END; ++i)
	{
		// Ư�� ��ü ����Ʈ�� ��ȸ
		for (auto iter = objList[i].begin(); iter != objList[i].end(); ++iter)
		{
			(*iter)->Update();
		}
	}
}

void Ingame::Render(HDC hdc)
{
	// ����ۿ� Ÿ�� ��� �׸���
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// ��ü ����Ʈ ������ŭ �ݺ�
	for (int i = 0; i < OBJ_END; ++i)
	{
		// Ư�� ��ü ����Ʈ�� ��ȸ
		for (auto iter = objList[i].begin(); iter != objList[i].end(); ++iter)
		{
			(*iter)->Render(bmpMap["BackBuffer"]->GetMemDC());
		}
	}

	// ����ۿ� �ʿ��� �� �� �׸� ��, ���������� ���
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmpMap["BackBuffer"]->GetMemDC(),
		0, 0, SRCCOPY);
}

void Ingame::Release()
{
	SafeDelete(bg);

	// ��ü ����Ʈ ������ŭ �ݺ�
	for (int i = 0; i < OBJ_END; ++i)
	{
		// Ư�� ��ü ����Ʈ�� ��ȸ
		for (auto iter = objList[i].begin(); iter != objList[i].end(); ++iter)
		{
			SafeDelete(*iter);
		}
		objList[i].clear();
	}
}

Ingame::Ingame()
{
}

Ingame::~Ingame()
{
	Release();
}
