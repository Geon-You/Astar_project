#include "MapEdit.h"
#include "Bitmap.h"

void MapEdit::Initialize()
{
	// �ؽ�ó �ε�
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
	// Ÿ�� �� �׸���
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			int idx = i * TILE_CNT_X + j;

			BitBlt(bmps[0]->GetMemDC(), // ����ۿ� �׸�
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				bmps[1]->GetMemDC(), // �׸� ���� hdc
				tiles[idx]->drawId * TILE_SIZE_X,// x �׸��� ������ ��ġ
				0,// y �׸��� ������ ��ġ
				SRCCOPY);
		}
	}

	// Ÿ�� ������ �׸���
	for (int i = 0; i < TILE_PRESET_CNT; ++i)
	{
		BitBlt(bmps[0]->GetMemDC(),
			i * TILE_SIZE_X + presetScrollX, // posX
			WIN_SIZE_Y - TILE_SIZE_Y, // posY
			TILE_SIZE_X, TILE_SIZE_Y, // size
			bmps[1]->GetMemDC(),
			i * TILE_SIZE_X, 0, // �̹��� �� �׸��� ������ ��ġ
			SRCCOPY);
	}

	// ������� ������ ���� ��� dc�� �׸�
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmps[0]->GetMemDC(), 0, 0, SRCCOPY);
}

void MapEdit::Release()
{
	// Ÿ�� ������ ���� �ҷ��� ���̹Ƿ�, ������ Ÿ�� ������ ����.
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

	// ���� ���콺�� ��ġ�� ��ǥ�� Ÿ���� x, y�࿡�� ��� °�� ��ġ�ϴ����� ���Ѵ�. (2���� ��Ŀ����� �ε���)
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

	// x ��ǥ�� Ÿ�� ������� ������, ���� Ÿ�� �ε����� ���� (������ ��ũ�� ����)
	selectedTile = (pt.x - presetScrollX) / TILE_SIZE_X;
}

void MapEdit::CheckKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// �������� Ŭ���� ��
		// ���콺 y��ǥ�� (������ ������ y - Ÿ�� ������ y) ���� ũ�ٸ�
		// ���� ���콺�� Ÿ�� ������ ������ ����
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (pt.y >= WIN_SIZE_Y - TILE_SIZE_Y)
			SelectPreset();
		// �ƴ϶��, Ÿ�� ��ġ ���������� Ŭ����
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
	// ���̺� �޽��� �˾�
	if (MessageBox(g_hWnd, L"Save?", L"System Message", MB_OKCANCEL) == IDCANCEL)
	{
		// ĵ���̶�� ����
		return;
	}

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// ������ ���� �۾�
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		WriteFile(handle, tiles[i], sizeof(TILE), &byte, NULL);
	}

	// �׻� �����͸� �а� ���� ���Ŀ��� �ڵ��� ������ �Ѵ�.
	CloseHandle(handle);
}

void MapEdit::LoadMap()
{
	// �ε� �޽��� �˾�
	if (MessageBox(g_hWnd, L"Load?", L"System Message", MB_OKCANCEL) == IDCANCEL)
	{
		// ĵ����ư�� �����ٸ� ����
		return;
	}

	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Ÿ�� ������ ���� �ҷ��� ���̹Ƿ�, ������ Ÿ�� ������ ����.
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

		// �� �̻� ���� �����Ͱ� ���� ���
		if (byte == 0)
		{
			// ���ʿ��� �� �� Ÿ�� �ν��Ͻ��� �����ϹǷ�,
			// �����͸� ä�� �ʿ䰡 ���� �ν��Ͻ��� �����ϰ�, Ż��
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