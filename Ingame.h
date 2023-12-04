#pragma once
#include "Scene.h"
#include "TileBackground.h"

class Object;
class Ingame :
    public Scene
{
private:
	Object* bg;
	list<Object*> objList[OBJ_END];

public:
	Object* GetTileBG() { return bg; }
	vector<TILE*>* GetTiles() 
	{ 
		if (bg == nullptr)
			return nullptr;

		return ((TileBackground*)bg)->GetTiles(); 
	}

public:
	// Scene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

public:
	Ingame();
	virtual ~Ingame();
};

