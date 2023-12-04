#pragma once
#include "Object.h"
class TileBackground :
    public Object
{
private:
	vector<TILE*> tiles;

public:
	static float scrollX, scrollY;
	float scrollSpeed;

public:
	vector<TILE*>* GetTiles() { return &tiles; }

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

public:
	void CheckKey();
	void Scroll();

public:
	TileBackground();
	virtual ~TileBackground();
};

