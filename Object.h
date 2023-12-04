#pragma once
#include "Include.h"

// 모든 게임 객체의 베이스가 될 추상 클래스
class Object abstract
{
protected:
	// 텍스처를 그릴 때, 사용할 키 값
	string drawKey;
	// 게임 객체들이 공통적으로 갖는 데이터를 선언
	INFO info;
	
	float speed;
	float dirX;
	float dirY;

	// 현재 각 씬 객체마다, 해당 씬에 필요한 텍스처(비트맵)를 map 컨테이너에 들고 있음
	// 이 때, 각 객체(액터)들은 자기 자신 또는 그 외 필요한 텍스처를 출력하기 위해선
	// 씬 객체가 갖고 있는 map에 접근해야 함
	// 이 때, 해당 map에 접근을 편리하게 하기 위해, map의 주소를 갖는 정적 필드를 선언
	static map<string, Bitmap*>* bmpMapAddress;

public:
	INFO GetInfo() { return info; }
	void SetDrawKey(string key) { drawKey = key; }
	void SetPos(int x, int y) { info.posX = x; info.posY = y; }
	RECT GetRect();

public:
	static void SetBmpMap(map<string, Bitmap*>* address)
	{
		bmpMapAddress = address;
	}

public:
	virtual void Initialize() abstract; // 모든 객체는 생성 후, 초기화 과정을 갖는다
	virtual SceneType Update() abstract; // 모든 객체는 특정 연산을 한다.
	virtual void Render(HDC hdc) abstract; // 모든 객체는 화면에 그려질 수 있다.
	virtual void Release() abstract; // 모든 객체는 파괴될 때, 동적메모리를 사용 중이라면 해제한다.

public:
	// 파라미터로 받은 위치에 해당하는 타일의 인덱스를 반환
	int GetTileIndex(float posX, float posY);
	// 길찾기 시작 기능
	void AStarStart(float startX, float startY, float goalX, float goalY);
	// 길찾기를 통해 얻은 경로를 따라 이동하는 기능
	void AStarMove();
	// 길이를 구하는 함수
	float GetDirection(float length);

public:
	Object();
	// 클래스 상속관계에서 다형성을 이용 시, 소멸자를 가상 소멸자로 만들지 않는다면
	// 정상적으로 소멸자가 호출되지 않음
	virtual ~Object(); 
};

