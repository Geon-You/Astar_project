#include "Object.h"
#include "SceneMgr.h"
#include "Ingame.h"
#include "AStar.h"

map<string, Bitmap*>* Object::bmpMapAddress = nullptr;

RECT Object::GetRect()
{
	RECT rc =
	{
		info.posX - info.sizeX / 2,
		info.posY - info.sizeY / 2,
		info.posX + info.sizeX / 2,
		info.posY + info.sizeY / 2
	};

	return rc;
}

int Object::GetTileIndex(float posX, float posY)
{
	int x = (posX - TileBackground::scrollX) / TILE_SIZE_X;
	int y = (posY - TileBackground::scrollY) / TILE_SIZE_Y;

    return y * TILE_CNT_X + x;
}

void Object::AStarStart(float startX, float startY, float goalX, float goalY)
{
	// 시작 위치의 타일 인덱스를 구함
	int startIdx = GetTileIndex(startX, startY);
	if (startIdx < 0 || startIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	// 도착 위치의 타일 인덱스를 구함
	int goalIdx = GetTileIndex(goalX, goalY);
	if (goalIdx < 0 || goalIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	// 구한 타일 인덱스를 기반으로 길찾기 시작
	AStar::GetInstance()->AStarStart(startIdx, goalIdx);
}

void Object::AStarMove()
{
	// 목적지까지 최적 경로인 타일들의 인덱스를 갖는 목록을 가져옴
	auto bestList = AStar::GetInstance()->GetBestList();

	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	// 최적 경로가 없을 경우
	if (bestList == nullptr || bestList->empty() || tiles == nullptr)
	{
		// 이동에 사용하는 방향 변수를 초기화하고 리턴
		dirX = 0;
		dirY = 0;
		return;
	}

	// 최적 경로 목록에서 맨 앞의 원소(이동할 타일 1개) 정보를 가져옴
	int destIdx = bestList->front();

	// 현재 타일에서 이동할 타일로의 방향을 구함

	// 각 축으로의 길이를 구함
	float distanceX = (*tiles)[destIdx]->posX - info.posX;
	float distanceY = (*tiles)[destIdx]->posY - info.posY;

	// 직선 거리를 구함
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// 타일 도착 판정을 위한 정지 거리를 지정하여 검사
	if (distance < 5.f)
	{
		// 이 곳에 들어왔다는 것은, 이동할 타일에 도착했다는 뜻
		// 최적 경로 목록에서 첫번째 원소를 꺼냄
		bestList->pop_front();
		return;
	}

	// 수평(x축), 수직(y축) 이동인지 확인
	auto isHorizontal = abs(distanceX) > abs(distanceY) ? true : false;

	// 각 축으로의 크기를 직선 거리로 나눠 방향만을 남김
	dirX = isHorizontal ? GetDirection(distanceX) : 0;
	dirY = isHorizontal ? 0 : GetDirection(distanceY);

	info.posX += dirX * speed;
	info.posY += dirY * speed;
}

float Object::GetDirection(float length)
{
	if (length > 0)
		return 1.f;
	else if (length < 0)
		return -1.f;

	return 0.0f;
}

Object::Object()
{
}

Object::~Object()
{
}
