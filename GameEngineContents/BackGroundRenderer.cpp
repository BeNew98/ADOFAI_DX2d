#include "PrecompileHeader.h"
#include "BackGroundRenderer.h"


#include <GameEngineCore/GameEngineLevel.h>


float4 BackGroundRenderer::m_pMonoChrome = float4::Null;

BackGroundRenderer::BackGroundRenderer() 
{
}

BackGroundRenderer::~BackGroundRenderer() 
{
}

void BackGroundRenderer::Start()
{
	PushCameraRender(-1);
	SetMesh("Rect");
	SetPipeLine("Mono");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue); 
	GetShaderResHelper().SetConstantBufferLink("MonoChrome", m_pMonoChrome);
}

void BackGroundRenderer::Update(float _Deltatime)
{
	GetLevel()->GetCamera(-1)->GetTransform()->SetWorldPosition(GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition());
}

