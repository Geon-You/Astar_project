#include "AStar.h"
#include "SceneMgr.h"
#include "Ingame.h"

AStar* AStar::instance = nullptr;

AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::AStarStart(int startIdx, int goalIdx)
{
	// �̵��� Ÿ���� ���� Ÿ�ϰ� �����ϴٸ� ����
	if (startIdx == goalIdx)
		return;

	// Ÿ�� ���� �ҷ�����
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// Ÿ�� ������ ���ٸ� ����
	if (tiles == nullptr)
		return;

	// ���� Ÿ���� ĳ���Ͱ� ������ �� ���� (�浹�ϴ�) Ÿ���̶�� ����
	if ((*tiles)[goalIdx]->isColl == true)
		return;

	// �̹� ���� ������ ���¿���, AStar�� �� ȣ��� ���
	// ������ �ִ� �����͵��� �����ϱ� ���� ȣ��
	// or �̹� ���� ��ã�⿡�� ���Ǿ��� �����͵��� �����ϴ� �뵵
	Release();

	this->startIdx = startIdx;
	this->goalIdx = goalIdx;

	// ��� ���� ����
	MakeRoute();
}

void AStar::MakeRoute()
{
	// Ÿ�� ���� �ҷ�����
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// Ÿ�� ������ ���ٸ� ����
	if (tiles == nullptr)
		return;

	// ���� ��� ����
	NODE* node = new NODE;
	// ����� Ÿ�� �ε����� ��ã�� ������ Ÿ�� �ε�����
	node->idx = startIdx;
	// �ش� ��尡 ���� ����̹Ƿ� �θ� ����
	node->parent = nullptr;
	node->cost = 0;

	// ���۳�带 �̹� ������ ������� ���
	closeList.push_back(node);

	// ���� Ÿ�� �˻� ��, ���Ƿ� Ÿ�� �ε����� ��� ��Ƶα� ���� ����
	int index = 0;

	while (true)
	{
		// ��
		index = node->idx - TILE_CNT_X; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� �迭 �ε���)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִ� �༮�� ����
		//  -> Ŭ����, ���� ����Ʈ�� �̹� �����Ѵٸ� ����
		if (index >= 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��,
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

		// �Ʒ�
		index = node->idx + TILE_CNT_X;
		if (index < (TILE_CNT_X * TILE_CNT_Y)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ������
		index = node->idx + 1;
		if (index < (TILE_CNT_X * TILE_CNT_Y) && index % TILE_CNT_X != 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ����
		index = node->idx - 1;
		if (index >= 0 && (index % TILE_CNT_X != TILE_CNT_X - 1)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index))
		{
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ���¸���Ʈ�� ����
		// -> ���(�Ÿ�)�� �������� ������������ ����
		openList.sort(Compare);

		// ���� ����Ʈ�� ����ִٸ�
		if (openList.empty())
			return;

		// ���� ����Ʈ���� �ڽ�Ʈ�� ���� ���� ��带 ������
		auto iter = openList.begin();
		// ����� ���� ���� ��带 ���� �˻翡 ����� ���� ����
		node = *iter;

		closeList.push_back(*iter);
		openList.erase(iter);

		// ���� �˻��� ���(����� ���� ���� Ÿ��)�� Ÿ�� �ε����� �� �ε����� ������ Ȯ��
		if (node->idx == goalIdx)
		{
			// �� �ε����� �����ߴٴ� ���� ��θ� ã�Ҵٴ� ��
			// ����, ������ ��� �����͸� ��´�.
			while (true)
			{
				// �˻� ��忡 �����Ͽ� ����(�θ� ���� ����)���� Ÿ�� �ε����� ����
				bestList.push_back(node->idx);
				node = node->parent;
				
				// ���������� �����ߴٸ� ����
				if (node->idx == startIdx)
					break;
			}
			bestList.reverse();

			return;
		}
	}
}

bool AStar::CheckList(int idx)
{
	// ���� or Ŭ���� ����Ʈ�� �����Ѵٸ� false
	// �ƴ϶�� true
	for (auto iter = openList.begin(); iter != openList.end(); ++iter)
	{
		if ((*iter)->idx == idx)
			return false;
	}

	for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
	{
		if ((*iter)->idx == idx)
			return false;
	}

	return true;
}

NODE* AStar::MakeNode(int idx, NODE* parent, vector<TILE*>* tiles)
{
	NODE* node = new NODE;
	node->idx = idx;
	node->parent = parent;

	// �θ� �������� �Ÿ�
	float distanceX = (*tiles)[parent->idx]->posX - (*tiles)[idx]->posX;
	float distanceY = (*tiles)[parent->idx]->posY - (*tiles)[idx]->posY;
	float gCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	// ���� �������� �Ÿ�
	float goalDistanceX = (*tiles)[goalIdx]->posX - (*tiles)[idx]->posX;
	float goalDistanceY = (*tiles)[goalIdx]->posY - (*tiles)[idx]->posY;
	float hCost = sqrt(goalDistanceX * goalDistanceX + goalDistanceY * goalDistanceY);

	node->cost = gCost + hCost;

	return node;
}

void AStar::Release()
{
	// ���� ����Ʈ ����
	for (auto iter = openList.begin(); iter != openList.end(); ++iter)
		SafeDelete(*iter);
	openList.clear();

	// Ŭ���� ����Ʈ ����
	for (auto iter = closeList.begin(); iter != closeList.end(); ++iter)
		SafeDelete(*iter);
	closeList.clear();

	// ���� ��� ����
	bestList.clear();
}
