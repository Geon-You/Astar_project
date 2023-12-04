#pragma once

class Object;

// 추상 팩토리
template<typename T>
class AbstractFactory
{
public:
	static Object* CreateObject()
	{
		Object* obj = new T();
		obj->Initialize();

		return obj;
	}

	static Object* CreateObject(int x, int y)
	{
		Object* obj = new T();
		obj->Initialize();
		obj->SetPos(x, y);

		return obj;
	}
};