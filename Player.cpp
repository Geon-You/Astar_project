#include "Player.h"
#include "Mouse.h"
#include "TileBackground.h"

void Player::Initialize()
{
	dirX = 0;
	dirY = 0;
	info.posX = WIN_SIZE_X / 2;
	info.posY = WIN_SIZE_Y / 2;
	info.sizeX = 200;
	info.sizeY = 200;

	// 초기 애니메이션 대기 모션으로 설정
	frame = FRAME(0, 0, 3, 100);
	// 초기 방향 설정 (어떤 방향의 텍스처를 그릴건지)
	drawKey = "Player_DOWN";

	speed = 3.f;
	prevAnimUpdateTime = GetTickCount64();
}

SceneType Player::Update()
{
	CheckKey();

	AStarMove();

	Direction();

	Motion();

	Frame();

    return SceneType::SCENE_NONE;
}

void Player::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc,
		info.posX - info.sizeX / 2,
		info.posY - info.sizeY / 2,
		info.sizeX, info.sizeY,
		(*bmpMapAddress)[drawKey]->GetMemDC(),
		info.sizeX * frame.current,
		info.sizeY * frame.animType,
		info.sizeX, info.sizeY,
		RGB(0,0,0));
}

void Player::Release()
{
}

void Player::CheckKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		auto mousePos = Mouse::GetPos();
		// 마우스 커서가 클라이언트 바깥 클릭이라면 AStarStart를 실행 안 하도록 수정해보기
		AStarStart(info.posX, info.posY, mousePos.x, mousePos.y);
	}
}

// 프레임 갱신
void Player::Frame()
{
	// 이전 프레임 갱신 시간에서 스프라이트 변경 인터벌 시간(time)을 더한 값이
	// 현재 틱 카운트보다 작다면 프레임을 갱신할 시간이라는 뜻
	auto t = GetTickCount64();
	if (prevAnimUpdateTime + frame.time < t)
	{
		// 새로 갱신하므로, 이전 갱신시간도 업데이트
		prevAnimUpdateTime = t;
		// 프레임을 다음 열로 이동
		++frame.current;

		// 현재 프레임 인덱스가 마지막 프레임 인덱스를 넘어섰다면
		if (frame.current > frame.last)
		{
			// 현재 프레임 인덱스를 초기화
			frame.current = 0;
		}
	}
}

void Player::Direction()
{
	// 이동 방향에 따라 drawKey를 변경
	//auto isHorizontal = abs(dirX) > abs(dirY);

	//if (isHorizontal)
	//{

	//}

	if (dirX > 0)
	{
		drawKey = "Player_RIGHT";
	}
	else if (dirX < 0)
	{
		drawKey = "Player_LEFT";
	}
	else
	{
		if (dirY > 0)
			drawKey = "Player_DOWN";
		else if (dirY < 0)
			drawKey = "Player_UP";
	}
}

void Player::Motion()
{
	dirX != 0 || dirY != 0 ? SetState(STATE_WALK) : SetState(STATE_IDLE);

	// 플레이어 상태(모션)에 따라 frame 필드를 변경하는 작업
	// 걷기 상태라면
	if (state & STATE_WALK)
	{
		frame.animType = 1;
		frame.last = 5;
	}

	// 대기 상태라면
	if (state & STATE_IDLE)
	{
		frame.animType = 0;
		frame.last = 3;
	}
}

void Player::SetState(DWORD newState)
{
	if (state != newState)
		frame.current = 0;

	state = newState;
}

Player::Player()
{
}

Player::~Player()
{
}
