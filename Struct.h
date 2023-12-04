#pragma once

// 특정 객체를 그릴 때, 위치와 사이즈가 필요
// 그럼 그 때 마다 위치와 사이즈를 매번 새로 선언하기 귀찮으니까
// 자주 사용되는 데이터를 구조체로 만들어 처리
typedef struct tagInfo
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
}INFO;

typedef struct tagTile
{
	// 타일 위치
	float posX;
	float posY;
	// 타일 사이즈
	float sizeX;
	float sizeY;
	// 텍스처 번호
	int drawId;
	// 해당 타입이 충돌 가능한지, 아닌지
	bool isColl;
}TILE;

// 애니메이션 처리에 사용되는 데이터를 모아놓은 구조체
typedef struct tagFrame
{
	bool isLoop; 
	int animType; // 현재 애니메이션 타입 (몇번째 행인지)
	int current; // 현재 애니메이션에서의 프레임 (몇번째 열인지)
	int last; // 현재 애니메이션의 마지막 열의 인덱스 (최대 프레임 수)
	DWORD time; // 현재 프레임에서 다음 프레임으로 변경할 때 걸리는 시간

	tagFrame() {}
	tagFrame(int animType, int current, int last, DWORD time)
		: animType(animType), current(current), last(last), time(time) {}
}FRAME;


typedef struct AStarNode
{
	float cost; // 비용 = 부모 노드까지의 거리 + 도착 노드까지의 거리
	int idx; // 타일 인덱스
	AStarNode* parent; // 시작점이 되는 노드
}NODE;