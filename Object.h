#pragma once
#include "Include.h"

// ��� ���� ��ü�� ���̽��� �� �߻� Ŭ����
class Object abstract
{
protected:
	// �ؽ�ó�� �׸� ��, ����� Ű ��
	string drawKey;
	// ���� ��ü���� ���������� ���� �����͸� ����
	INFO info;
	
	float speed;
	float dirX;
	float dirY;

	// ���� �� �� ��ü����, �ش� ���� �ʿ��� �ؽ�ó(��Ʈ��)�� map �����̳ʿ� ��� ����
	// �� ��, �� ��ü(����)���� �ڱ� �ڽ� �Ǵ� �� �� �ʿ��� �ؽ�ó�� ����ϱ� ���ؼ�
	// �� ��ü�� ���� �ִ� map�� �����ؾ� ��
	// �� ��, �ش� map�� ������ ���ϰ� �ϱ� ����, map�� �ּҸ� ���� ���� �ʵ带 ����
	static map<string, Bitmap*>* bmpMapAddress;

public:
	INFO GetInfo() { return info; }
	void SetDrawKey(string key) { drawKey = key; }
	void SetPos(int x, int y) { info.posX = x; info.posY = y; }
	RECT GetRect();

public:
	static void SetBmpMap(map<string, Bitmap*>* address)
	{
		bmpMapAddress = address;
	}

public:
	virtual void Initialize() abstract; // ��� ��ü�� ���� ��, �ʱ�ȭ ������ ���´�
	virtual SceneType Update() abstract; // ��� ��ü�� Ư�� ������ �Ѵ�.
	virtual void Render(HDC hdc) abstract; // ��� ��ü�� ȭ�鿡 �׷��� �� �ִ�.
	virtual void Release() abstract; // ��� ��ü�� �ı��� ��, �����޸𸮸� ��� ���̶�� �����Ѵ�.

public:
	// �Ķ���ͷ� ���� ��ġ�� �ش��ϴ� Ÿ���� �ε����� ��ȯ
	int GetTileIndex(float posX, float posY);
	// ��ã�� ���� ���
	void AStarStart(float startX, float startY, float goalX, float goalY);
	// ��ã�⸦ ���� ���� ��θ� ���� �̵��ϴ� ���
	void AStarMove();
	// ���̸� ���ϴ� �Լ�
	float GetDirection(float length);

public:
	Object();
	// Ŭ���� ��Ӱ��迡�� �������� �̿� ��, �Ҹ��ڸ� ���� �Ҹ��ڷ� ������ �ʴ´ٸ�
	// ���������� �Ҹ��ڰ� ȣ����� ����
	virtual ~Object(); 
};

