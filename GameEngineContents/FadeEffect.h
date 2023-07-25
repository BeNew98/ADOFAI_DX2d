#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class FadeState
{
	None,
	FadeIn,
	FadeOut,
};

// Ό³Έν :
class FadeEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	FadeEffect();
	~FadeEffect();

	// delete Function
	FadeEffect(const FadeEffect& _Other) = delete;
	FadeEffect(FadeEffect&& _Other) noexcept = delete;
	FadeEffect& operator=(const FadeEffect& _Other) = delete;
	FadeEffect& operator=(FadeEffect&& _Other) noexcept = delete;

	void FadeIn() 
	{
		State = FadeState::FadeIn;
		FadeData.x = 0.0f;
	}

	void FadeOut() 
	{
		State = FadeState::FadeOut;
		FadeData.x = 1.0f;
	}
	void SetWhite()
	{
		FadeData.y = 1.f;
	}
	void SetTimeRatio(float _Ratio)
	{
		m_fTimeRatio = _Ratio;
	}


protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	float4 FadeData = {1.0f, 0.0f, 0.0f, 1.0f};
	float m_fTimeRatio = 0.f;
	FadeState State = FadeState::None;

	std::shared_ptr<GameEngineRenderUnit> FadeUnit;

};

