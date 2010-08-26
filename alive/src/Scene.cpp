#include "Scene.h"

namespace alive {
	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::init(Input* input) { mInput = input; }

	void Scene::setModelName(char* modelFileName) { mFileToLoad = modelFileName; }
}
