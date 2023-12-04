#pragma once
#include "Include.h"

class Scene abstract
{
protected:
	// map의 key와 value로 쌍(pair)을 이룸
	// key는 데이터를 식별할 식별자
	// value는 실제 활용하고자하는 데이터
	map<string, Bitmap*> bmpMap;

public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
	virtual void Release() abstract;

	// 씬 객체 파괴 시, 해당 씬이 들고있던 bmp들을 메모리 해제하는 기능
	void ClearBmpMap();

public:
	Scene();
	virtual ~Scene();
};

