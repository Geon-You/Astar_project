#pragma once
#include "Define.h"

class MainGame
{
private:
	HDC hdc; // ���� �� ��ü�� �׸� �� ���� hdc

public:
	void Initialize(); // �ʱ�ȭ
	void Update(); // ���� �� ����
	void Render(); // �׸���
	void Release(); // �޸� ����

public:
	MainGame();
	~MainGame();
};

