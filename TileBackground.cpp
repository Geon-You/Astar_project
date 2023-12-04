#include "TileBackground.h"

float TileBackground::scrollX = 0;
float TileBackground::scrollY = 0;

void TileBackground::Initialize()
{
	drawKey = "Tile";
	scrollX = 0;
	scrollY = 0;
	scrollSpeed = 5.f;

	HANDLE handle;
	DWORD byte;

	// CreateFile 함수의 파라미터를 바꾸면 파일 열기도 가능
	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (true)
	{
		TILE* tile = new TILE;

		ReadFile(handle, tile, sizeof(TILE), &byte, NULL);

		// 더 이상 읽을 데이터가 없을 경우
		if (byte == 0)
		{
			// 위쪽에서 매 번 타일 인스턴스를 생성하므로,
			// 데이터를 채울 필요가 없는 인스턴스를 제거하고, 탈출
			SafeDelete(tile);
			break;
		}

		tiles.push_back(tile);
	}

	CloseHandle(handle);
}

SceneType TileBackground::Update()
{
	return SCENE_NONE;
}

void TileBackground::Render(HDC hdc)
{
	// 타일 맵 그리기
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			int idx = i * TILE_CNT_X + j;

			BitBlt(hdc, // 백버퍼에 그림
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				(*bmpMapAddress)[drawKey]->GetMemDC(), // 그릴 원본 hdc
				tiles[idx]->drawId * TILE_SIZE_X,// x 그리기 시작할 위치
				0,// y 그리기 시작할 위치
				SRCCOPY);
		}
	}
}

void TileBackground::Release()
{
	// 타일 정보를 새로 불러올 것이므로, 기존의 타일 정보를 비운다.
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		SafeDelete(tiles[i]);
	}
	tiles.clear();
}

TileBackground::TileBackground()
{
}

TileBackground::~TileBackground()
{
	Release();
}
