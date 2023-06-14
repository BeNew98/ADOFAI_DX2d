#include "PrecompileHeader.h"
#include "BackGroundRenderer.h"

BackGroundRenderer::BackGroundRenderer() 
{
}

BackGroundRenderer::~BackGroundRenderer() 
{
}

void BackGroundRenderer::Start()
{
	PushCameraRender(-1);
	SpriteRenderInit();
}

