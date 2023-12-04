#include "Button.h"
#include "Mouse.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"

void Button::Initialize()
{
	isHover = 0;
	info.sizeX = 150;
	info.sizeY = 150;
}

SceneType Button::Update()
{
	// ��ư�� �簢�� ���� ������ ������
	auto rc = GetRect();

	// Ư�� ����Ʈ(���콺 ��ġ)�� �簢�� ���� �ȿ� �ִ� �� Ȯ��
	if (PtInRect(&rc, Mouse::GetPos()))
	{
		// ��ư ���� �ȿ� ���콺�� ��ġ�� ���
		isHover = 1;

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// ��ư�� ���� �߰����� ���� ó��
			if (drawKey == "StartBtn")
			{
				// ���� ��ü���� ������ �ν��Ͻ��� ������,
				// ������ �ν��Ͻ��� ������ ����Ʈ�� ���� �����̳ʿ� ��Ƽ� �� ���� ������Ʈ �Ѵ�.
				// �׷� �� ��, �ش� ��ü���� ���� ���������� �����ϰ� �� ��,
				// ��ü�� ������Ʈ�� ����� ��, for������ ���� ������ ����
				// �̹� �ı��� ��(���� �ı��ǹǷ� �����̳ʵ� �ı���)���� ���� ��ü�� �Ѿ�� �ϱ� ������ ������ �߻���

				// ���� ���� ������ �ذ��ϱ� ����, ��ü���� ���������� ���� �������� �ʰ�,
				// ���� ���� �Ǵ� �������� �ʰڴٴ� �÷��׸� ��ȯ�ϴ� ������� ���
				// 
				// SceneMgr::GetInstance()->SetScene(SCENE_INGAME);
				return SCENE_INGAME;
			}
		}
	}
	else
	{
		// ��ư ���� �ȿ� ���콺�� ��ġ���� ���� ���
		isHover = 0;
	}

	return SCENE_NONE;
}

void Button::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc, // ��� �׸�����
		info.posX - info.sizeX / 2, // x
		info.posY - info.sizeY / 2, // y
		info.sizeX, info.sizeY, // size
		(*bmpMapAddress)[drawKey]->GetMemDC(), // ���� �ؽ��ĸ� ���� dc
		info.sizeX * isHover, 0, // �̹��� ������ �׸��� ������ ��ġ x,y
		info.sizeX, info.sizeY, // �̹��� ������ �󸶸�ŭ ������� �׸�����
		RGB(255, 255, 255) // � ���� ���� �����Ұ���
	);
}

void Button::Release()
{
}

Object* Button::CreateButton(float x, float y, string drawkey)
{
	Object* button = AbstractFactory<Button>::CreateObject(x, y);
	button->SetDrawKey(drawkey);

	return button;
}

Button::Button()
{
}

Button::~Button()
{
}
