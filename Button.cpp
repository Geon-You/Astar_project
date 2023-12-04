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
	// 버튼의 사각형 영역 정보를 가져옴
	auto rc = GetRect();

	// 특정 포인트(마우스 위치)가 사각형 영역 안에 있는 지 확인
	if (PtInRect(&rc, Mouse::GetPos()))
	{
		// 버튼 영역 안에 마우스가 위치한 경우
		isHover = 1;

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// 버튼에 따른 추가적인 동작 처리
			if (drawKey == "StartBtn")
			{
				// 보통 객체들은 복수의 인스턴스를 가지고,
				// 복수의 인스턴스를 씬에서 리스트와 같은 컨테이너에 담아서 한 번에 업데이트 한다.
				// 그럼 이 때, 해당 객체에서 씬을 직접적으로 변경하게 될 시,
				// 객체의 업데이트가 종료된 후, for문에서 증감 연산을 통해
				// 이미 파괴된 씬(씬이 파괴되므로 컨테이너도 파괴됨)에서 다음 객체로 넘어가려 하기 때문에 에러가 발생함

				// 위와 같은 문제를 해결하기 위헤, 객체에서 직접적으로 씬을 변경하지 않고,
				// 씬을 변경 또는 변경하지 않겠다는 플래그를 반환하는 방식으로 사용
				// 
				// SceneMgr::GetInstance()->SetScene(SCENE_INGAME);
				return SCENE_INGAME;
			}
		}
	}
	else
	{
		// 버튼 영역 안에 마우스가 위치하지 않은 경우
		isHover = 0;
	}

	return SCENE_NONE;
}

void Button::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc, // 어디에 그릴건지
		info.posX - info.sizeX / 2, // x
		info.posY - info.sizeY / 2, // y
		info.sizeX, info.sizeY, // size
		(*bmpMapAddress)[drawKey]->GetMemDC(), // 원본 텍스쳐를 갖는 dc
		info.sizeX * isHover, 0, // 이미지 내에서 그리기 시작할 위치 x,y
		info.sizeX, info.sizeY, // 이미지 내에서 얼마만큼 사이즈로 그릴건지
		RGB(255, 255, 255) // 어떤 색상 값을 제외할건지
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
