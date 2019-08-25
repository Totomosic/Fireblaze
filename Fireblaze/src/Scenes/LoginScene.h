#pragma once
#include "Common/LoginRequests.h"
#include "Common/LoginResponses.h"

namespace Fireblaze
{

	FBL_API void CreateLoginScene(Scene& scene, int width, int height, Scene& registerScene, Scene& characterSelectScene);

}