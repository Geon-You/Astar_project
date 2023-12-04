#pragma once

class Object;

// �߻� ���丮
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