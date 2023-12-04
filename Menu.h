#pragma once
#include "Scene.h"

class Object;
class Menu :
    public Scene
{
private:
	Object* bg;
	list<Object*> buttons;

public:
	// Scene��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

public:
	Menu();
	virtual ~Menu();
};

