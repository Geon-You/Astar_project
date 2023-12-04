#pragma once

// 씬 종류를 열거
enum SceneType
{
	SCENE_NONE = -1, // 업데이트 반환 값으로 사용 씬을 변경하지 않는다는 의미
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_INGAME,
	SCENE_END,
};

// 인게임 내 액터의 종류를 열거
enum ObjType
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_END,
};

// 플레이어 상태 정의 (비트 연산을 통해 복수의 데이터를 하나의 변수로 나타낼 수 있다.)
const DWORD STATE_IDLE = 0b00000001;
const DWORD STATE_WALK = 0b00000010;
const DWORD STATE_ATK  = 0b00000100;
const DWORD STATE_HIT  = 0b00001000;
const DWORD STATE_DEAD = 0b00010000;

// 타일 프리셋 수
const int TILE_PRESET_CNT = 24;

// 타일 하나의 사이즈
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt X * cnt Y 로 맵의 크기가 결정
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;