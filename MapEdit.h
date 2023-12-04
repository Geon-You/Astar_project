#pragma once
#include "Object.h"

class Bitmap;

class MapEdit :
    public Object
{
private:
    // 객체의 삽입, 제거가 빈번하다면 list
// 객체의 수가 어느 정도 정해져 있고 객체를 지정하여 접근하고 싶다면 vector
    vector<TILE*> tiles;
    vector<Bitmap*> bmps;

    // 현재 선택한 타일 프리셋의 인덱스
    int selectedTile;
    // 화면 스크롤링에 사용할 x, y 
    float scrollX;
    float scrollY;
    // 타일 프리셋 x축 스크롤에 사용할 값
    float presetScrollX;
    float speed;

public:
    // Object을(를) 통해 상속됨
    void Initialize() override;
	SceneType Update() override;
    void Render(HDC hdc) override;
    void Release() override;

public:
    void InitTile(); // 초기 타일 생성 기능
    TILE* CreateTile(float x, float y); // 타일 생성 기능
    void Picking(int drawId); // 맵 내에 특정 타일을 클릭 시, 프리셋 설정 값을 적용하는 기능
    void SelectPreset(); // 프리셋 영역에서 특정 타일 프리셋 선택 시, 프리셋 인덱스 변경 기능
    void CheckKey(); 
    void Scroll();
    void SaveMap();
    void LoadMap();

public:
    MapEdit();
    virtual ~MapEdit();
};

