#pragma once

// Ư�� ��ü�� �׸� ��, ��ġ�� ����� �ʿ�
// �׷� �� �� ���� ��ġ�� ����� �Ź� ���� �����ϱ� �������ϱ�
// ���� ���Ǵ� �����͸� ����ü�� ����� ó��
typedef struct tagInfo
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
}INFO;

typedef struct tagTile
{
	// Ÿ�� ��ġ
	float posX;
	float posY;
	// Ÿ�� ������
	float sizeX;
	float sizeY;
	// �ؽ�ó ��ȣ
	int drawId;
	// �ش� Ÿ���� �浹 ��������, �ƴ���
	bool isColl;
}TILE;

// �ִϸ��̼� ó���� ���Ǵ� �����͸� ��Ƴ��� ����ü
typedef struct tagFrame
{
	bool isLoop; 
	int animType; // ���� �ִϸ��̼� Ÿ�� (���° ������)
	int current; // ���� �ִϸ��̼ǿ����� ������ (���° ������)
	int last; // ���� �ִϸ��̼��� ������ ���� �ε��� (�ִ� ������ ��)
	DWORD time; // ���� �����ӿ��� ���� ���������� ������ �� �ɸ��� �ð�

	tagFrame() {}
	tagFrame(int animType, int current, int last, DWORD time)
		: animType(animType), current(current), last(last), time(time) {}
}FRAME;


typedef struct AStarNode
{
	float cost; // ��� = �θ� �������� �Ÿ� + ���� �������� �Ÿ�
	int idx; // Ÿ�� �ε���
	AStarNode* parent; // �������� �Ǵ� ���
}NODE;