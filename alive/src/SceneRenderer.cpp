#include "SceneRenderer.h"

namespace alive {
	SceneRenderer::SceneRenderer() {}
	SceneRenderer::~SceneRenderer() {}

	void SceneRenderer::init(Input* input) { mInput = input; }

	void SceneRenderer::setModelName(char* modelFileName) { mFileToLoad = modelFileName; }
}
