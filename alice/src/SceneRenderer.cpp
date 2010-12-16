#include "SceneRenderer.h"

namespace alice {
	SceneRenderer::SceneRenderer() {}
	SceneRenderer::~SceneRenderer() {}

	void SceneRenderer::init(InputHandler* input) { mInput = input; }
}
