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
	// 객체 리스트 종류만큼 반복
	for (int i = 0; i < OBJ_END; ++i)
	{
		// 특정 객체 리스트를 순회
		for (auto iter = objList[i].begin(); iter != objList[i].end(); ++iter)
		{
			(*iter)->Update();
		}
	}
}

void Ingame::Render(HDC hdc)
{
	// 백버퍼에 타일 배경 그리기
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 객체 리스트 종류만큼 반복
	for (int i = 0; i < OBJ_END; ++i)
	{
		// 특정 객체 리스트를 순회
		for (auto iter = objList[i].begin(); iter != objList[i].end(); ++iter)
		{
			(*iter)->Render(bmpMap["BackBuffer"]->GetMemDC());
		}
	}

	// 백버퍼에 필요한 걸 다 그린 후, 최종적으로 출력
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmpMap["BackBuffer"]->GetMemDC(),
		0, 0, SRCCOPY);
}

void Ingame::Release()
{
	SafeDelete(bg);

	// 객체 리스트 종류만큼 반복
	for (int i = 0; i < OBJ_END; ++i)
	{
		// 특정 객체 리스트를 순회
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
