#pragma once
#include "Define.h"

class Bitmap
{
private:
	HDC hdc, memDC;
	HBITMAP bitmap, oldBitmap;

public:
	HDC GetMemDC() { return memDC; }
	Bitmap* LoadBmp(const WCHAR* filePath);
	void Release();

public:
	Bitmap();
	~Bitmap();
};

