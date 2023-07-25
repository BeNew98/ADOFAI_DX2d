#include "PrecompileHeader.h"
#include "FadeEffect.h"

FadeEffect::FadeEffect() 
{
}

FadeEffect::~FadeEffect() 
{
}

void FadeEffect::Start(GameEngineRenderTarget* _Target)
{
	FadeUnit = std::make_shared<GameEngineRenderUnit>();
	FadeUnit->SetMesh("FullRect");
	FadeUnit->SetPipeLine("Fade");

	FadeUnit->ShaderResHelper.SetConstantBufferLink("FADEDATA", FadeData);
	// 
	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void FadeEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	float fTime = m_fTimeRatio * _DeltaTime;
	if (State == FadeState::None)
	{
		return;
	}

	if (State == FadeState::FadeOut && 1.0f <= FadeData.x)
	{
		return;
	}

	if (State == FadeState::FadeOut)
	{
		FadeData.x -= fTime;

	}
	else 
	{
		FadeData.x += fTime;
	}


	ResultTarget->Clear();
	FadeUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	ResultTarget->Setting();
	FadeUnit->Render(fTime);
	FadeUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);

	int a = 0;
}