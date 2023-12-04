#pragma once
#include "Include.h"

class Scene abstract
{
protected:
	// map�� key�� value�� ��(pair)�� �̷�
	// key�� �����͸� �ĺ��� �ĺ���
	// value�� ���� Ȱ���ϰ����ϴ� ������
	map<string, Bitmap*> bmpMap;

public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
	virtual void Release() abstract;

	// �� ��ü �ı� ��, �ش� ���� ����ִ� bmp���� �޸� �����ϴ� ���
	void ClearBmpMap();

public:
	Scene();
	virtual ~Scene();
};

