#pragma once
#include "Object.h"
class Player :
    public Object
{
private:
	DWORD prevAnimUpdateTime; // ���� �ִϸ��̼� ���� �ð�
	FRAME frame;
	// �÷��̾� ����
	DWORD state;

public:
	// Object��(��) ���� ��ӵ�
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

