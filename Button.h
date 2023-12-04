#pragma once
#include "Object.h"
class Button :
    public Object
{
private:
	// ���콺���� ���ͷ��� ���� (0 �̶�� ��Ȱ��ȭ, 1 �̶�� Ȱ��ȭ)
	int isHover;

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

public:
	// �ܺο��� ��ư ������ ���ϰ� �ϱ� ���� ���
	static Object* CreateButton(float x, float y, string drawkey);

public:
	Button();
	virtual ~Button();
};

