#pragma once
#include "Object.h"
class Button :
    public Object
{
private:
	// 마우스와의 인터렉션 여부 (0 이라면 비활성화, 1 이라면 활성화)
	int isHover;

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

public:
	// 외부에서 버튼 생성을 편리하게 하기 위한 기능
	static Object* CreateButton(float x, float y, string drawkey);

public:
	Button();
	virtual ~Button();
};

