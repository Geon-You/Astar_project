#include "Scene.h"

void Scene::ClearBmpMap()
{
	for (auto iter = bmpMap.begin(); iter != bmpMap.end(); ++iter)
	{
		SafeDelete(iter->second); // second°¡ value, first´Â key
	}
	bmpMap.clear();
}

Scene::Scene()
{
}

Scene::~Scene()
{
	ClearBmpMap();
}
