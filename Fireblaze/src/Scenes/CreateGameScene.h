#pragma once
#include "Common/LoginRequests.h"
#include "Common/LoginResponses.h"

namespace Fireblaze
{

	FBL_API void CreateGameScene(Scene& scene, int width, int height, Scene& loginScene, Scene& characterSelectScene);

}