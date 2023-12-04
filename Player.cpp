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

	// �ʱ� �ִϸ��̼� ��� ������� ����
	frame = FRAME(0, 0, 3, 100);
	// �ʱ� ���� ���� (� ������ �ؽ�ó�� �׸�����)
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
		// ���콺 Ŀ���� Ŭ���̾�Ʈ �ٱ� Ŭ���̶�� AStarStart�� ���� �� �ϵ��� �����غ���
		AStarStart(info.posX, info.posY, mousePos.x, mousePos.y);
	}
}

// ������ ����
void Player::Frame()
{
	// ���� ������ ���� �ð����� ��������Ʈ ���� ���͹� �ð�(time)�� ���� ����
	// ���� ƽ ī��Ʈ���� �۴ٸ� �������� ������ �ð��̶�� ��
	auto t = GetTickCount64();
	if (prevAnimUpdateTime + frame.time < t)
	{
		// ���� �����ϹǷ�, ���� ���Žð��� ������Ʈ
		prevAnimUpdateTime = t;
		// �������� ���� ���� �̵�
		++frame.current;

		// ���� ������ �ε����� ������ ������ �ε����� �Ѿ�ٸ�
		if (frame.current > frame.last)
		{
			// ���� ������ �ε����� �ʱ�ȭ
			frame.current = 0;
		}
	}
}

void Player::Direction()
{
	// �̵� ���⿡ ���� drawKey�� ����
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

	// �÷��̾� ����(���)�� ���� frame �ʵ带 �����ϴ� �۾�
	// �ȱ� ���¶��
	if (state & STATE_WALK)
	{
		frame.animType = 1;
		frame.last = 5;
	}

	// ��� ���¶��
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
