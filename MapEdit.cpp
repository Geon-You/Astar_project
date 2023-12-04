#include "MapEdit.h"
#include "Bitmap.h"

void MapEdit::Initialize()
{
	// 텍스처 로딩
	bmps.push_back((new Bitmap)->LoadBmp(L"BackBuffer.bmp"));
	bmps.push_back((new Bitmap)->LoadBmp(L"Tile.bmp"));

	selectedTile = 0;
	InitTile();

	speed = 5.f;
	presetScrollX = 0;
	scrollX = 0;
	scrollY = 0;
}

SceneType MapEdit::Update()
{
	CheckKey();
	Scroll();

	return SCENE_NONE;
}

void MapEdit::Render(HDC hdc)
{
	// 타일 맵 그리기
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			int idx = i * TILE_CNT_X + j;

			BitBlt(bmps[0]->GetMemDC(), // 백버퍼에 그림
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				bmps[1]->GetMemDC(), // 그릴 원본 hdc
				tiles[idx]->drawId * TILE_SIZE_X,// x 그리기 시작할 위치
				0,// y 그리기 시작할 위치
				SRCCOPY);
		}
	}

	// 타일 프리셋 그리기
	for (int i = 0; i < TILE_PRESET_CNT; ++i)
	{
		BitBlt(bmps[0]->GetMemDC(),
			i * TILE_SIZE_X + presetScrollX, // posX
			WIN_SIZE_Y - TILE_SIZE_Y, // posY
			TILE_SIZE_X, TILE_SIZE_Y, // size
			bmps[1]->GetMemDC(),
			i * TILE_SIZE_X, 0, // 이미지 내 그리기 시작할 위치
			SRCCOPY);
	}

	// 백버퍼의 내용을 최종 출력 dc에 그림
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmps[0]->GetMemDC(), 0, 0, SRCCOPY);
}

void MapEdit::Release()
{
	// 타일 정보를 새로 불러올 것이므로, 기존의 타일 정보를 비운다.
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i])
		{
			delete tiles[i];
			tiles[i] = nullptr;
		}
	}
	tiles.clear();

	for (size_t i = 0; i < bmps.size(); ++i)
	{
		if (bmps[i])
		{
			delete bmps[i];
			bmps[i] = nullptr;
		}
	}
	bmps.clear();
}

void MapEdit::InitTile()
{
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			float x = (j * TILE_SIZE_X) + TILE_SIZE_X / 2;
			float y = (i * TILE_SIZE_Y) + TILE_SIZE_Y / 2;

			tiles.push_back(CreateTile(x, y));
		}
	}
}

TILE* MapEdit::CreateTile(float x, float y)
{
	TILE* tile = new TILE;

	tile->posX = x;
	tile->posY = y;
	tile->sizeX = TILE_SIZE_X;
	tile->sizeY = TILE_SIZE_Y;
	tile->drawId = 0;
	tile->isColl = false;

	return tile;
}

void MapEdit::Picking(int drawId)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// 현재 마우스가 위치한 좌표의 타일이 x, y축에서 몇번 째에 위치하는지를 구한다. (2차원 행렬에서의 인덱스)
	int x = (pt.x - scrollX) / TILE_SIZE_X;
	int y = (pt.y - scrollY) / TILE_SIZE_Y;
	
	int tileIndex = y * TILE_CNT_X + x;

	tiles[tileIndex]->drawId = drawId;
}

void MapEdit::SelectPreset()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// x 좌표를 타일 사이즈로 나누어, 현재 타일 인덱스를 구함 (프리셋 스크롤 고려)
	selectedTile = (pt.x - presetScrollX) / TILE_SIZE_X;
}

void MapEdit::CheckKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// 프리셋을 클릭할 때
		// 마우스 y좌표가 (윈도우 사이즈 y - 타일 사이즈 y) 보다 크다면
		// 현재 마우스는 타일 프리셋 영역에 있음
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (pt.y >= WIN_SIZE_Y - TILE_SIZE_Y)
			SelectPreset();
		// 아니라면, 타일 배치 영역에서의 클릭임
		else
			Picking(selectedTile);
	}

	if (GetAsyncKeyState(VK_LEFT))
		scrollX += speed;

	if (GetAsyncKeyState(VK_RIGHT))
		scrollX -= speed;

	if (GetAsyncKeyState(VK_UP))
		scrollY += speed;

	if (GetAsyncKeyState(VK_DOWN))
		scrollY -= speed;

	if (GetAsyncKeyState('A'))
		presetScrollX += speed;

	if (GetAsyncKeyState('D'))
		presetScrollX -= speed;

	if (GetAsyncKeyState('S'))
		SaveMap();

	if (GetAsyncKeyState('L'))
		LoadMap();
}

void MapEdit::Scroll()
{
	if (scrollX > 0)
		scrollX = 0;

	if (scrollY > 0)
		scrollY = 0;

	if (scrollX < WIN_SIZE_X - (TILE_CNT_X * TILE_SIZE_X))
	{
		scrollX = WIN_SIZE_X - (TILE_CNT_X * TILE_SIZE_X);
	}

	if (scrollY < WIN_SIZE_Y - (TILE_CNT_Y * TILE_SIZE_Y))
	{
		scrollY = WIN_SIZE_Y - (TILE_CNT_Y * TILE_SIZE_Y);
	}

	if (presetScrollX > 0)
		presetScrollX = 0;

	if (presetScrollX < WIN_SIZE_X - (TILE_PRESET_CNT * TILE_SIZE_X))
		presetScrollX = WIN_SIZE_X - (TILE_PRESET_CNT * TILE_SIZE_X);
}

void MapEdit::SaveMap()
{
	// 세이브 메시지 팝업
	if (MessageBox(g_hWnd, L"Save?", L"System Message", MB_OKCANCEL) == IDCANCEL)
	{
		// 캔슬이라면 리턴
		return;
	}

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 데이터 쓰기 작업
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		WriteFile(handle, tiles[i], sizeof(TILE), &byte, NULL);
	}

	// 항상 데이터를 읽고 쓰기 이후에는 핸들을 잠궈줘야 한다.
	CloseHandle(handle);
}

void MapEdit::LoadMap()
{
	// 로드 메시지 팝업
	if (MessageBox(g_hWnd, L"Load?", L"System Message", MB_OKCANCEL) == IDCANCEL)
	{
		// 캔슬버튼을 눌렀다면 리턴
		return;
	}

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 타일 정보를 새로 불러올 것이므로, 기존의 타일 정보를 비운다.
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i])
		{
			delete tiles[i];
			tiles[i] = nullptr;
		}
	}
	tiles.clear();

	while (true)
	{
		TILE* tile = new TILE;

		ReadFile(handle, tile, sizeof(TILE), &byte, NULL);

		// 더 이상 읽을 데이터가 없을 경우
		if (byte == 0)
		{
			// 위쪽에서 매 번 타일 인스턴스를 생성하므로,
			// 데이터를 채울 필요가 없는 인스턴스를 제거하고, 탈출
			delete tile;
			break;
		}

		tiles.push_back(tile);
	}

	CloseHandle(handle);
}

MapEdit::MapEdit()
{
}

MapEdit::~MapEdit()
{
	Release();
}
