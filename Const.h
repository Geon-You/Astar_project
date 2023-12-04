#pragma once

// �� ������ ����
enum SceneType
{
	SCENE_NONE = -1, // ������Ʈ ��ȯ ������ ��� ���� �������� �ʴ´ٴ� �ǹ�
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_INGAME,
	SCENE_END,
};

// �ΰ��� �� ������ ������ ����
enum ObjType
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_END,
};

// �÷��̾� ���� ���� (��Ʈ ������ ���� ������ �����͸� �ϳ��� ������ ��Ÿ�� �� �ִ�.)
const DWORD STATE_IDLE = 0b00000001;
const DWORD STATE_WALK = 0b00000010;
const DWORD STATE_ATK  = 0b00000100;
const DWORD STATE_HIT  = 0b00001000;
const DWORD STATE_DEAD = 0b00010000;

// Ÿ�� ������ ��
const int TILE_PRESET_CNT = 24;

// Ÿ�� �ϳ��� ������
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt X * cnt Y �� ���� ũ�Ⱑ ����
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;