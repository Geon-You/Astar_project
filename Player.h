#pragma once
#include "Object.h"
class Player :
    public Object
{
private:
	DWORD prevAnimUpdateTime; // 이전 애니메이션 갱신 시간
	FRAME frame;
	// 플레이어 상태
	DWORD state;

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

private:
	void CheckKey();
	void Frame();
	void Direction();
	void Motion();
	void SetState(DWORD newState);

public:
	Player();
	virtual ~Player();
};

