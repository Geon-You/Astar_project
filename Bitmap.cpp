#include "Bitmap.h"

Bitmap* Bitmap::LoadBmp(const WCHAR* filePath)
{
	// 윈도우에서 기본 dc를 가져옴
	hdc = GetDC(g_hWnd);
	// dc를 하나 생성함
	memDC = CreateCompatibleDC(hdc);

	// 파라미터로 받은 bmp 경로를 통해 이미지를 불러옴
	bitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// memDC에 불러온 bitmap을 설정하고, memDC가 이전에 들고 있던
	// bmp을 oldBitmap에 담아둠
	oldBitmap = (HBITMAP)SelectObject(memDC, bitmap);

	// hdc는 복제 생성하기 위한 용도로 가져왔음
	// memDC를 생성했으니 hdc의 사용이 끝났으므로 반환
	ReleaseDC(g_hWnd, hdc);

	// 비트맵 인스턴스 자기 자신을 반환
	// 결과 해당 인스턴스에 memDC에 그리고자 하는 bitmap이 있음
	return this;
}

void Bitmap::Release()
{
	SelectObject(memDC, oldBitmap);
	DeleteObject(bitmap);
	DeleteDC(memDC);
}

Bitmap::Bitmap()
{
}

Bitmap::~Bitmap()
{
	Release();
}
