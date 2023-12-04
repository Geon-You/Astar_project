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
	// ���� ��ġ�� Ÿ�� �ε����� ����
	int startIdx = GetTileIndex(startX, startY);
	if (startIdx < 0 || startIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	// ���� ��ġ�� Ÿ�� �ε����� ����
	int goalIdx = GetTileIndex(goalX, goalY);
	if (goalIdx < 0 || goalIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	// ���� Ÿ�� �ε����� ������� ��ã�� ����
	AStar::GetInstance()->AStarStart(startIdx, goalIdx);
}

void Object::AStarMove()
{
	// ���������� ���� ����� Ÿ�ϵ��� �ε����� ���� ����� ������
	auto bestList = AStar::GetInstance()->GetBestList();

	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	// ���� ��ΰ� ���� ���
	if (bestList == nullptr || bestList->empty() || tiles == nullptr)
	{
		// �̵��� ����ϴ� ���� ������ �ʱ�ȭ�ϰ� ����
		dirX = 0;
		dirY = 0;
		return;
	}

	// ���� ��� ��Ͽ��� �� ���� ����(�̵��� Ÿ�� 1��) ������ ������
	int destIdx = bestList->front();

	// ���� Ÿ�Ͽ��� �̵��� Ÿ�Ϸ��� ������ ����

	// �� �������� ���̸� ����
	float distanceX = (*tiles)[destIdx]->posX - info.posX;
	float distanceY = (*tiles)[destIdx]->posY - info.posY;

	// ���� �Ÿ��� ����
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// Ÿ�� ���� ������ ���� ���� �Ÿ��� �����Ͽ� �˻�
	if (distance < 5.f)
	{
		// �� ���� ���Դٴ� ����, �̵��� Ÿ�Ͽ� �����ߴٴ� ��
		// ���� ��� ��Ͽ��� ù��° ���Ҹ� ����
		bestList->pop_front();
		return;
	}

	// ����(x��), ����(y��) �̵����� Ȯ��
	auto isHorizontal = abs(distanceX) > abs(distanceY) ? true : false;

	// �� �������� ũ�⸦ ���� �Ÿ��� ���� ���⸸�� ����
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
